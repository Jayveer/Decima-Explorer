#include "DecimaArchive.h"
#include "DecimaArchiveError.h"

bool DecimaArchive::checkMagic() {
	return (header.magic == 0x20304050) || (header.magic == 0x21304050);
}

bool DecimaArchive::isEncrypted() {
	return header.magic == 0x21304050;
}

std::string DecimaArchive::getFilename() {
	return filename;
}

void DecimaArchive::setFilename(std::string filename) {
	this->filename = filename;
}

DecimaArchive::DecimaArchive() {

}

DecimaArchive::DecimaArchive(std::string filename) {
	setFilename(filename);
}

int DecimaArchive::getVersion() {
	return header.key;
}

DecimaArchive::~DecimaArchive() {
}

uint64_t DecimaArchive::calculateFirstContainingChunk(uint64_t fileOffset, int chunkSize) {
	return fileOffset - (fileOffset % chunkSize);
}

uint64_t DecimaArchive::calculateLastContainingChunk(uint64_t fileOffset, int fileSize, int chunkSize) {
	return calculateFirstContainingChunk(fileOffset + fileSize, chunkSize);
}

int DecimaArchive::calculateChunkTableOffset(uint64_t fileTableCount) {
	return fileTableCount * 0x20 + 0x28;
}

void DecimaArchive::parseHeader(FILE* f) {
	fread(&header.magic, 4, 1, f);
	fread(&header.key, 4, 1, f);
	fread(&header.fileSize, 8, 1, f);
	fread(&header.dataSize, 8, 1, f);
	fread(&header.fileTableCount, 8, 1, f);
	fread(&header.chunkTableCount, 4, 1, f);
	fread(&header.maxChunkSize, 4, 1, f);
}

void DecimaArchive::parseFileTable(FILE* f, uint64_t fileTableCount) {
	for (int i = 0; i < fileTableCount; i++) {
		DecimaFileEntry fileEntry;

		fread(&fileEntry.entryNum, 4, 1, f);
		fread(&fileEntry.key, 4, 1, f);
		fread(&fileEntry.hash, 8, 1, f);
		fread(&fileEntry.offset, 8, 1, f);
		fread(&fileEntry.size, 4, 1, f);
		fread(&fileEntry.key2, 4, 1, f);

		fileTable.push_back(fileEntry);
	}
}

void DecimaArchive::parseChunkTable(FILE* f, uint64_t chunkTableCount) {
	for (int i = 0; i < chunkTableCount; i++) {

		DecimaChunkEntry chunkEntry;

		fread(&chunkEntry.uncompressedOffset, 8, 1, f);
		fread(&chunkEntry.uncompressedSize, 4, 1, f);
		fread(&chunkEntry.key, 4, 1, f);
		fread(&chunkEntry.compressedOffset, 8, 1, f);
		fread(&chunkEntry.compressedSize, 4, 1, f);
		fread(&chunkEntry.key2, 4, 1, f);

		chunkTable.push_back(chunkEntry);
	}
}

DataBuffer DecimaArchive::getChunkData(DecimaChunkEntry chunkEntry) {
	uint64_t chunkOffset = chunkEntry.compressedOffset;
	uint64_t chunkSize = chunkEntry.compressedSize;
	DataBuffer dataBuffer(chunkSize);
	FILE *f;
	
	fopen_s(&f, getFilename().c_str(), "rb");
	_fseeki64(f, chunkOffset, SEEK_SET);
	fread(&dataBuffer[0], 1, chunkSize, f);

	return dataBuffer;
}

void DecimaArchive::decompressChunkData(DataBuffer data, uint64_t decompressedSize, unsigned char *output) {
	int res = Kraken_Decompress(&data[0], data.size(), output, decompressedSize);
	if (res == -1) showError(DECOMPRESSFAIL);
}

uint32_t DecimaArchive::getFileEntryIndex(int id) {
	for (int i = 0; i < fileTable.size(); i++) {
		if (fileTable[i].entryNum == id)
			return i;
	}
	return -1;
}

uint64_t DecimaArchive::getFileHash(std::string filename) {
	uint64_t hash;
	uint8_t byte[16];
	MurmurHash3_x64_128(filename.c_str(), filename.size() + 1, seed, &byte);
	memcpy(&hash, byte, 8);
	return hash;
}

uint32_t DecimaArchive::getFileEntryIndex(std::string filename) {
	uint64_t hash = getFileHash(filename);
	for (int i = 0; i < fileTable.size(); i++) {
		if (fileTable[i].hash == hash)
			return i;
	}
	return -1;
}

DecimaFileEntry DecimaArchive::getFileEntry(int id) {
	for (int i = 0; i < fileTable.size(); i++) {
		if (fileTable[i].entryNum == id)
			return fileTable[i];
	}
}


int DecimaArchive::findChunkWithOffset(uint64_t offset) {
	for (int i = 0; i < chunkTable.size(); i++) {
		if (chunkTable[i].uncompressedOffset == offset)
			return i;
	}
}

int DecimaArchive::writeDataToFile(DataBuffer data, std::string filename) {
	FILE *f;
	fopen_s(&f, filename.c_str(), "wb");

	if (!f) {
		showError(WRITEFAIL);
		return 0;
	}

	fseek(f, 0, SEEK_END);
	fwrite(&data[0], 1, data.size(), f);
	fclose(f);
}

DataBuffer DecimaArchive::extract(DecimaFileEntry fileEntry) {
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

void DecimaArchive::decryptHeader() {
	uint32_t* p = (uint32_t*)&header + 2;
	cipher(header.key, header.key + 1, p);
}

void DecimaArchive::decryptFileTable() {
	for (int i = 0; i< header.fileTableCount; i++) {
		uint32_t* p = (uint32_t*)&fileTable[i];
		cipher(fileTable[i].key, fileTable[i].key2, p);
	}
}

void DecimaArchive::decryptChunkTable() {
	for (int i = 0; i < header.chunkTableCount; i++) {
		uint32_t* p = (uint32_t*)&chunkTable[i];
		uint32_t saveKey = chunkTable[i].key;
		cipher(chunkTable[i].key, chunkTable[i].key2, p);
		chunkTable[i].key = saveKey;
	}
}

void DecimaArchive::decryptChunkData(int32_t id, DataBuffer* data) {
	dataCipher(id, &(*data)[0], data->size());
}

void DecimaArchive::cipher(uint32_t key, uint32_t key2, uint32_t *src) {
	uint32_t iv[4];
	uint32_t inputKey[2][4] = {
								{ key,  murmurSalt[1], murmurSalt[2], murmurSalt[3] }, 
								{ key2, murmurSalt[1], murmurSalt[2], murmurSalt[3] } 
	};

	for (int i = 0; i < 2; i++) {
		MurmurHash3_x64_128(inputKey[i], 0x10, seed, iv);
		for (int j = 0; j < 4; j++) {
			src[(i * 4) + j] ^= iv[j];
		}
	}
}

void DecimaArchive::dataCipher(uint32_t chunkID, uint8_t* src, int size) {
	uint32_t iv[4];
	MurmurHash3_x64_128(&chunkTable[chunkID].uncompressedOffset, 0x10, seed, iv);

	for (int i = 0; i < 4; i++) {
		iv[i] ^= murmurSalt2[i];
	}

	md5_byte_t* digest = md5Hash((md5_byte_t*)iv, 16);

	for (int i = 0; i < size; i++) {
		src[i] ^= digest[i % 16];
	}
}

int DecimaArchive::open() {
	FILE *f;
	fopen_s(&f, getFilename().c_str(), "rb");

	if (!f) {
		showError(OPENFAIL);
		return 0;
	}

	parseHeader(f);

	if (!checkMagic()) {
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

int DecimaArchive::extractFile(uint32_t id, std::string output) {
	uint32_t i = getFileEntryIndex(id);

	if (i == -1) {
		showError(FINDINDEXFAIL);
		return 0;
	}

	DataBuffer data = extract(fileTable[i]);
	if (!writeDataToFile(data, output)) return 0;
	return 1;
}

int DecimaArchive::extractFile(std::string filename, std::string output) {
	if (!hasExtension(filename, "core")) addExtension(filename, "core");
	uint32_t i = getFileEntryIndex(filename);

	if (i == -1) {
		showError(INVALIDFILENAME);
		return 0;
	}

	DataBuffer data = extract(fileTable[i]);
	if (!writeDataToFile(data, output)) return 0;
	return 1;
}

DataBuffer DecimaArchive::extractFile(std::string filename) {
	DataBuffer data;
	if (!hasExtension(filename, "core")) addExtension(filename, "core");
	uint32_t i = getFileEntryIndex(filename);

	if (i == -1) {
		showError(INVALIDFILENAME);
		return data;
	}

	data =  extract(fileTable[i]);
	return data;
}
