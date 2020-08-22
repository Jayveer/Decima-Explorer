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

uint64_t ArchiveBin::calculateFileTableSize() {
	return this->fileTable.size() * 0x20;
}

uint64_t ArchiveBin::calculateChunkTableSize() {
	return this->chunkTable.size() * 0x20;
}

uint64_t ArchiveBin::calculateChunkTableSize(uint64_t numChunks) {
	return numChunks * 0x20;
}

uint64_t ArchiveBin::calculateChunkTableOffset() {
	return calculateFileTableSize() + 0x28;
}

uint64_t ArchiveBin::calculateDataOffset() {
	return calculateChunkTableOffset() + calculateChunkTableSize();
}

uint64_t ArchiveBin::calculateDataOffset(uint64_t numChunks) {
	return calculateChunkTableOffset() + calculateChunkTableSize(numChunks);
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

void ArchiveBin::writeHeader(FILE* f) {
	fwrite(&header.magic, 4, 1, f);
	fwrite(&header.key, 4, 1, f);
	fwrite(&header.fileSize, 8, 1, f);
	fwrite(&header.dataSize, 8, 1, f);
	fwrite(&header.fileTableCount, 8, 1, f);
	fwrite(&header.chunkTableCount, 4, 1, f);
	fwrite(&header.maxChunkSize, 4, 1, f);
}

void ArchiveBin::writeFileTable(FILE* f) {
	for (int i = 0; i < fileTable.size(); i++) {
		fwrite(&fileTable[i].entryNum, 4, 1, f);
		fwrite(&fileTable[i].key, 4, 1, f);
		fwrite(&fileTable[i].hash, 8, 1, f);
		fwrite(&fileTable[i].offset, 8, 1, f);
		fwrite(&fileTable[i].size, 4, 1, f);
		fwrite(&fileTable[i].key2, 4, 1, f);
	}
}

void ArchiveBin::writeChunkTable(FILE* f) {
	for (int i = 0; i < chunkTable.size(); i++) {
		fwrite(&chunkTable[i].uncompressedOffset, 8, 1, f);
		fwrite(&chunkTable[i].uncompressedSize, 4, 1, f);
		fwrite(&chunkTable[i].key, 4, 1, f);
		fwrite(&chunkTable[i].compressedOffset, 8, 1, f);
		fwrite(&chunkTable[i].compressedSize, 4, 1, f);
		fwrite(&chunkTable[i].key2, 4, 1, f);
	}
}

void ArchiveBin::writeChunkData(FILE* f, const std::vector<DataBuffer>& chunks) {
	for (int i = 0; i < chunks.size(); i++) {
		fwrite(&chunks[i][0], chunks[i].size(), 1, f);
	}
}

void ArchiveBin::addChunkData(std::vector<DataBuffer>& chunks) {
	FILE* f;
	fopen_s(&f, getFilename().c_str(), "ab");
	
	for (int i = 0; i < chunks.size(); i++) {
		uint64_t chunkIdx = chunkTable.size() - chunks.size() + i;
		if (isEncrypted()) decryptChunkData(chunkIdx, &chunks[i]);
	}

	writeChunkData(f, chunks);

	for (int i = 0; i < chunks.size(); i++) {
		uint64_t chunkIdx = chunkTable.size() - chunks.size() + i;
		if (isEncrypted()) decryptChunkData(chunkIdx, &chunks[i]);
	}

	fclose(f);
}

void ArchiveBin::updateHeader() {
	FILE* f;
	fopen_s(&f, getFilename().c_str(), "r+b");
	if (isEncrypted()) decryptHeader();
	writeHeader(f);
	if (isEncrypted()) decryptHeader();
	fclose(f);
}

void ArchiveBin::updateFileTable() {
	FILE* f;
	fopen_s(&f, getFilename().c_str(), "r+b");
	fseek(f, 0x28, SEEK_SET);
	if (isEncrypted()) decryptFileTable();
	writeFileTable(f);
	if (isEncrypted()) decryptFileTable();
	fclose(f);
}

void ArchiveBin::updateChunkTable() {
	FILE* f;
	fopen_s(&f, getFilename().c_str(), "r+b");
	fseek(f, calculateChunkTableOffset(), SEEK_SET);
	if (isEncrypted()) decryptChunkTable();
	writeChunkTable(f);
	if (isEncrypted()) decryptChunkTable();
	fclose(f);
}

void ArchiveBin::addChunkTable(const std::vector<DataBuffer>& chunks) {
	uint64_t increasedSize = chunks.size() * 0x20;
	for (int i = 0; i < chunkTable.size(); i++) {
		chunkTable[i].compressedOffset += increasedSize;
	}

	uint64_t dataOffset = calculateDataOffset() - increasedSize;
	shiftData(getFilename(), dataOffset, increasedSize);

	updateChunkTable();
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

int ArchiveBin::compressChunkData(unsigned char* input, uint64_t decompressedSize, DataBuffer& output) {
	char* chunkHeap = new char[(uint64_t)header.maxChunkSize + 65536];
	int compressedSize = Kraken_Compress(input, decompressedSize, (byte*)chunkHeap);

	if (compressedSize == -1) {
		showError(COMPRESSFAIL);
		delete[] chunkHeap;
		return -1;
	}

	output.resize(compressedSize);
	memcpy(&output[0], chunkHeap, compressedSize);
	delete[] chunkHeap;
	return compressedSize;
}

void ArchiveBin::decompressChunkData(const DataBuffer &data, uint64_t decompressedSize, unsigned char* output) {
	int res = Kraken_Decompress(&data[0], data.size(), output, decompressedSize);
	if (res == -1) showError(DECOMPRESSFAIL);
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
		uint8_t* data = &chunkData[0];
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
		uint32_t saveKey = fileTable[i].key;
		uint32_t saveKey2 = fileTable[i].key2;
		decrypt(fileTable[i].key, fileTable[i].key2, p);
		fileTable[i].key = saveKey;
		fileTable[i].key2 = saveKey2;
	}
}

void ArchiveBin::decryptChunkTable() {
	for (int i = 0; i < header.chunkTableCount; i++) {
		uint32_t* p = (uint32_t*)&chunkTable[i];
		uint32_t saveKey = chunkTable[i].key;
		uint32_t saveKey2 = chunkTable[i].key2;
		decrypt(chunkTable[i].key, chunkTable[i].key2, p);
		chunkTable[i].key = saveKey;
		chunkTable[i].key2 = saveKey2;
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

void updateFileEntry(uint32_t id, int64_t offset = -1, int64_t size = -1, int64_t hash = -1, int32_t key = -1, int32_t key2 = -1) {

}

void createFileEntry(uint32_t id, int64_t offset, int64_t size, int64_t hash, int32_t key, int32_t key2) {

}


DataBuffer ArchiveBin::createFileEntries(const std::string& basePath, const std::vector<std::string>& fileList, bool isUpdate = 0) {
	DataBuffer buffer;
	uint64_t pos = isUpdate ? header.dataSize : 0;

	for (int i = 0; i < fileList.size(); i++) {
		FILE* f;
		std::string file = basePath + "\\" + fileList[i];
		fopen_s(&f, file.c_str(), "rb");

		if (!f) continue;

		uint32_t filesize = getFilesize(f);

		if (isUpdate) {
			uint32_t idx = getFileEntryIndex(fileList[i].c_str());
			if (idx == -1) continue;
			std::cout << fileList[i] << " will be updated\n";
			fileTable[idx].offset = pos;
			fileTable[idx].size = filesize;
		} else {
			BinFileEntry fileEntry;
			fileEntry.entryNum = i;
			fileEntry.hash = getFileHash(fileList[i].c_str());
			fileEntry.key = 0;
			fileEntry.key2 = 0;
			fileEntry.offset = pos;
			fileEntry.size = filesize;
			fileTable.push_back(fileEntry);
		}

		int writePos = isUpdate ? pos - header.dataSize : pos;

		buffer.resize(buffer.size() + filesize);
		fread(&buffer[writePos], filesize, 1, f);
		fclose(f);

		pos += filesize;
	}

	header.fileTableCount = fileTable.size();
	header.dataSize = pos;
	return buffer;
}

uint64_t ArchiveBin::getUncompressedSizeEnd() {
	uint32_t lastChunkIdx = chunkTable.size() - 1;
	uint64_t lastCompressedSize = chunkTable[lastChunkIdx].uncompressedSize;
	uint64_t lastCompressedOffset = chunkTable[lastChunkIdx].uncompressedOffset;
	return lastCompressedOffset + lastCompressedSize;
}

std::vector<DataBuffer> ArchiveBin::createChunkEntries(DataBuffer& buffer, bool isUpdate = 0) {
	std::vector<DataBuffer> chunkedFile;
	
	int numChunks = (buffer.size() / header.maxChunkSize);
	int remainder = buffer.size() % header.maxChunkSize;
	if (remainder) numChunks++;

	header.chunkTableCount = isUpdate ? header.chunkTableCount + numChunks : numChunks;

	uint64_t uncompressedEnd = isUpdate ? getUncompressedSizeEnd() : 0;
	uint64_t pos = isUpdate ? uncompressedEnd : 0;
	uint64_t compPos = isUpdate ? header.fileSize : calculateDataOffset(numChunks);

	for (int i = 0; i < numChunks; i++) {
		uint64_t size = header.maxChunkSize;
		bool isLastChunk = i == numChunks - 1;

		if (isLastChunk && remainder) size = remainder;
		
		DataBuffer chunk;
		int readPos = isUpdate ? pos - uncompressedEnd : pos;
		int compressedSize = compressChunkData(&buffer[readPos], size, chunk);
		if (compressedSize == -1) continue;

		BinChunkEntry chunkEntry;
		chunkEntry.uncompressedOffset = pos;
		chunkEntry.uncompressedSize = size;
		chunkEntry.key = 0x02F927DA;
		chunkEntry.compressedOffset = compPos;
		chunkEntry.compressedSize = compressedSize;
		chunkEntry.key2 = 0x02F927DA;

		pos += size;
		compPos += compressedSize;
		chunkedFile.push_back(chunk);
		chunkTable.push_back(chunkEntry);
	}
	
	header.fileSize = compPos;
	return chunkedFile;
}

void ArchiveBin::nukeHashes(const std::vector<std::string>& fileList) {
	bool wasChanged = false;

	for (int i = 0; i < fileList.size(); i++) {
		if (nukeHash(fileList[i])) wasChanged = true;
	}

	if (wasChanged) updateFileTable();
}

int ArchiveBin::nukeHash(const std::string& filename) {
	uint32_t i = getFileEntryIndex(filename);
	if (i == -1) return 0;
	std::cout << "overwriting " + filename + " in " + getFilename();
	fileTable[i].hash = 0;
	return 1;
}

int ArchiveBin::create(const std::string& basePath, const std::vector<std::string>& fileList) {
	header.magic = 0x20304050;
	header.key = 0x7FF6;
	header.maxChunkSize = 0x40000;

	DataBuffer buffer = createFileEntries(basePath, fileList);
	std::vector<DataBuffer> chunks = createChunkEntries(buffer);

	FILE* f;
	fopen_s(&f, getFilename().c_str(), "wb");

	writeHeader(f);
	writeFileTable(f);
	writeChunkTable(f);
	writeChunkData(f, chunks);

	fclose(f);
	return 0;
}

int ArchiveBin::update(const std::string& basePath, const std::vector<std::string>& fileList) {
	DataBuffer buffer = createFileEntries(basePath, fileList, 1);
	std::vector<DataBuffer> chunks = createChunkEntries(buffer, 1);

	std::cout << "repacking...\n";

	updateHeader();
	updateFileTable();
	addChunkTable(chunks);
	addChunkData(chunks); 

	std::cout << "finished repacking\n";

	return 1;
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
