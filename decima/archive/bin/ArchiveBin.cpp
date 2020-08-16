#include "ArchiveBin.h"
#include <errno.h>

ArchiveBin::ArchiveBin(std::string filename) : DecimaArchive(filename, this->extension) {

}

ArchiveBin::~ArchiveBin() {

}

bool ArchiveBin::checkMagic() {
	return (header.magic == 0x20304050) || (header.magic == 0x21304050);
}

uint32_t ArchiveBin::getMagic() {
	return header.magic;
}

uint64_t ArchiveBin::calculateFirstContainingChunk(uint64_t fileOffset, int chunkSize) {
	return fileOffset - (fileOffset % chunkSize);
}

uint64_t ArchiveBin::calculateLastContainingChunk(uint64_t fileOffset, int fileSize, int chunkSize) {
	return calculateFirstContainingChunk(fileOffset + fileSize, chunkSize);
}

int ArchiveBin::calculateChunkTableOffset(uint64_t fileTableCount) {
	return fileTableCount * 0x20 + 0x28;
}

void ArchiveBin::parseHeader(FILE* f) {
	fread(&header.magic, 4, 1, f);
	fread(&header.key, 4, 1, f);
	fread(&header.fileSize, 8, 1, f);
	fread(&header.dataSize, 8, 1, f);
	fread(&header.fileTableCount, 8, 1, f);
	fread(&header.chunkTableCount, 4, 1, f);
	fread(&header.maxChunkSize, 4, 1, f);
}

//void ArchiveBin::createHeader() {
//
//}

void ArchiveBin::parseFileTable(FILE* f, uint64_t fileTableCount) {
	for (int i = 0; i < fileTableCount; i++) {
		BinFileEntry fileEntry;

		fread(&fileEntry.entryNum, 4, 1, f);
		fread(&fileEntry.key, 4, 1, f);
		fread(&fileEntry.hash, 8, 1, f);
		fread(&fileEntry.offset, 8, 1, f);
		fread(&fileEntry.size, 4, 1, f);
		fread(&fileEntry.key2, 4, 1, f);

		fileTable.push_back(fileEntry);
	}
}

void ArchiveBin::parseChunkTable(FILE* f, uint64_t chunkTableCount) {
	for (int i = 0; i < chunkTableCount; i++) {

		BinChunkEntry chunkEntry;

		fread(&chunkEntry.uncompressedOffset, 8, 1, f);
		fread(&chunkEntry.uncompressedSize, 4, 1, f);
		fread(&chunkEntry.key, 4, 1, f);
		fread(&chunkEntry.compressedOffset, 8, 1, f);
		fread(&chunkEntry.compressedSize, 4, 1, f);
		fread(&chunkEntry.key2, 4, 1, f);

		chunkTable.push_back(chunkEntry);
	}
}

DataBuffer ArchiveBin::getChunkData(BinChunkEntry chunkEntry) {
	uint64_t chunkOffset = chunkEntry.compressedOffset;
	uint64_t chunkSize = chunkEntry.compressedSize;
	DataBuffer dataBuffer(chunkSize);
	FILE* f;

	fopen_s(&f, getFilename().c_str(), "rb");

	if (!f) {
		showError(WRITEFAIL);
		return dataBuffer;
	}

	_fseeki64(f, chunkOffset, SEEK_SET);
	fread(&dataBuffer[0], 1, chunkSize, f);

	fclose(f);

	return dataBuffer;
}

void ArchiveBin::decompressChunkData(const DataBuffer &data, uint64_t decompressedSize, unsigned char* output) {
	int res = Kraken_Decompress(&data[0], data.size(), output, decompressedSize);
	if (res == -1) showError(DECOMPRESSFAIL);
}

int ArchiveBin::compressChunkData(const DataBuffer& data, uint64_t decompressedSize, unsigned char* output) {
	int res = Kraken_Compress((uint8*)&data[0], decompressedSize, output);
	if (res == -1) showError(DECOMPRESSFAIL);
	return res;
}

uint32_t ArchiveBin::getFileEntryIndex(int id) {
	for (int i = 0; i < fileTable.size(); i++) {
		if (fileTable[i].entryNum == id)
			return i;
	}
	return -1;
}

uint32_t ArchiveBin::getFileEntryIndex(const std::string& filename) {
	uint64_t hash = getFileHash(filename);
	for (int i = 0; i < fileTable.size(); i++) {
		if (fileTable[i].hash == hash)
			return i;
	}
	return -1;
}

BinFileEntry ArchiveBin::getFileEntry(int id) {
	for (int i = 0; i < fileTable.size(); i++) {
		if (fileTable[i].entryNum == id)
			return fileTable[i];
	}
}


int ArchiveBin::findChunkWithOffset(uint64_t offset) {
	for (int i = 0; i < chunkTable.size(); i++) {
		if (chunkTable[i].uncompressedOffset == offset)
			return i;
	}
}

DataBuffer ArchiveBin::extract(BinFileEntry fileEntry) {
	uint64_t fileOffset = fileEntry.offset;
	uint32_t fileSize = fileEntry.size;

	uint64_t firstChunk = calculateFirstContainingChunk(fileOffset, header.maxChunkSize);
	uint64_t lastChunk = calculateLastContainingChunk(fileOffset, fileSize, header.maxChunkSize);

	uint64_t firstChunkRow = findChunkWithOffset(firstChunk);
	uint64_t lastChunkRow = findChunkWithOffset(lastChunk);
	uint64_t maxNeededSize = ((lastChunkRow - firstChunkRow) + 1) * header.maxChunkSize;

	int pos = 0;
	DataBuffer tempBuffer(maxNeededSize);

	for (int i = firstChunkRow; i <= lastChunkRow; i++) {
		DataBuffer chunkData = getChunkData(chunkTable[i]);
		
		if (isEncrypted()) decryptChunkData(i, &chunkData);
		decompressChunkData(chunkData, chunkTable[i].uncompressedSize, &tempBuffer[pos]);
		pos += chunkTable[i].uncompressedSize;
	}

	uint64_t filePosition = fileOffset % header.maxChunkSize;

	DataBuffer file(fileSize);

	memcpy(&file[0], &tempBuffer[filePosition], fileSize);

	return file;

}

void ArchiveBin::decryptHeader() {
	uint32_t* p = (uint32_t*)&header + 2;
	decrypt(header.key, header.key + 1, p);
}

void ArchiveBin::decryptFileTable() {
	for (int i = 0; i < header.fileTableCount; i++) {
		uint32_t* p = (uint32_t*)&fileTable[i];
		decrypt(fileTable[i].key, fileTable[i].key2, p);
	}
}

void ArchiveBin::decryptChunkTable() {
	for (int i = 0; i < header.chunkTableCount; i++) {
		uint32_t* p = (uint32_t*)&chunkTable[i];
		uint32_t saveKey = chunkTable[i].key;
		decrypt(chunkTable[i].key, chunkTable[i].key2, p);
		chunkTable[i].key = saveKey;
	}
}

void ArchiveBin::decryptChunkData(int32_t id, DataBuffer* data) {
	uint32_t* p = (uint32_t*)&chunkTable[id];
	dataDecrypt(p, &(*data)[0], data->size());
}

int ArchiveBin::open() {
	FILE* f;
	

	fopen_s(&f, getFilename().c_str(), "rb");

	if (!f) {
		showError(OPENFAIL);
		return 0;
	}

	parseHeader(f);

	if (!checkMagic()) {
		fclose(f);
		showError(INVALIDMAGIC);
		return 0;
	}

	if (isEncrypted()) decryptHeader();

	parseFileTable(f, header.fileTableCount);
	if (isEncrypted()) decryptFileTable();

	parseChunkTable(f, header.chunkTableCount);
	if (isEncrypted()) decryptChunkTable();

	fclose(f);
	return 1;
}

std::vector<DataBuffer> compress(const std::string& filename) {
	std::vector<DataBuffer> chunkedFile;

	FILE* f;
	fopen_s(&f, filename.c_str(), "rb");

	if (!f) return chunkedFile;

	_fseeki64(f, 0, SEEK_END);
	uint64_t filesize = ftell(f);
	_fseeki64(f, 0, SEEK_SET);

	int nchunks = (filesize / 0x40000);
	int remainder = filesize % 0x40000;
	if (remainder) nchunks++;

	for (int i = 0; i < nchunks; i++) {
		DataBuffer fileChunk;
		int size = i == nchunks - 1 ? remainder : 0x40000;
		fileChunk.resize(size);

		fread(&fileChunk[0], size, 1, f);

		DataBuffer chunk;
		chunk.resize(0x40000);
		int compressedSize = Kraken_Compress(&fileChunk[0], size, &chunk[0]);
		chunk.resize(compressedSize);
		chunkedFile.push_back(chunk);
	}
	
	return chunkedFile;
}

BinChunkEntry createChunkEntry(const std::vector<DataBuffer>& chunks) {
	for (int i = 0; i < chunks.size(); i++) {
		BinChunkEntry chunk;
		chunk.compressedSize = chunks[i].size();
		chunk.key = 0;
		chunk.key2 = 0;
	}
}

int ArchiveBin::create(const std::string& basePath, const std::vector<std::string>& fileList) {
	std::string filePath = basePath + "\\" + fileList[0];
	std::vector<DataBuffer> chunks = compress(filePath);
	


	return 0;
}

int ArchiveBin::extractFile(uint32_t id, std::string output) {
	if (!hasExtension(output, "core")) addExtension(output, "core");

	uint32_t i = getFileEntryIndex(id);

	if (i == -1) {
		showError(FINDINDEXFAIL);
		return 0;
	}

	DataBuffer data = extract(fileTable[i]);
	if (!writeDataToFile(data, output)) return 0;
	return 1;
}

int ArchiveBin::extractFile(std::string filename, std::string output, bool suppressError) {
	if (!hasExtension(filename, "core")) addExtension(filename, "core");
	if (!hasExtension(output, "core")) addExtension(output, "core");
	uint32_t i = getFileEntryIndex(filename);

	if (i == -1) {
		if (!suppressError) showError(INVALIDFILENAME);
		return 0;
	}

	DataBuffer data = extract(fileTable[i]);
	if (!writeDataToFile(data, output)) return 0;
	return 1;
}

DataBuffer ArchiveBin::extractFile(std::string filename) {
	DataBuffer data;
	if (!hasExtension(filename, "core")) addExtension(filename, "core");
	uint32_t i = getFileEntryIndex(filename);

	if (i == -1) {
		showError(INVALIDFILENAME);
		return data;
	}

	data = extract(fileTable[i]);
	return data;
}
