#include "DecimaArchive.h"
#include "DecimaArchiveError.h"

bool DecimaArchive::checkMagic() {
	return header.magic == 0x20304050;
}

std::string DecimaArchive::getFilename() {
	return filename;
}

void DecimaArchive::setFilename(std::string filename) {
	this->filename = filename;
}

DecimaArchive::DecimaArchive(std::string filename) {
	setFilename(filename);
}

int DecimaArchive::getVersion() {
	return header.version;
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
	fread(&header.version, 4, 1, f);
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
		fread(&fileEntry.unknown, 4, 1, f);
		fread(&fileEntry.unknown2, 8, 1, f);
		fread(&fileEntry.offset, 8, 1, f);
		fread(&fileEntry.size, 4, 1, f);
		fread(&fileEntry.unknown3, 4, 1, f);

		fileTable.push_back(fileEntry);
	}
}

void DecimaArchive::parseChunkTable(FILE* f, uint64_t chunkTableCount) {
	for (int i = 0; i < chunkTableCount; i++) {

		DecimaChunkEntry chunkEntry;

		fread(&chunkEntry.uncompressedOffset, 8, 1, f);
		fread(&chunkEntry.uncompressedSize, 4, 1, f);
		fread(&chunkEntry.unknown, 4, 1, f);
		fread(&chunkEntry.compressedOffset, 8, 1, f);
		fread(&chunkEntry.compressedSize, 4, 1, f);
		fread(&chunkEntry.unknown2, 4, 1, f);

		chunkTable.push_back(chunkEntry);
	}
}

DataBuffer DecimaArchive::getChunkData(DecimaChunkEntry chunkEntry) {
	int chunkOffset = chunkEntry.compressedOffset;
	int chunkSize = chunkEntry.compressedSize;
	DataBuffer dataBuffer(chunkSize);
	FILE *f;

	fopen_s(&f, getFilename().c_str(), "rb");
	fseek(f, chunkOffset, SEEK_SET);
	fread(&dataBuffer[0], 1, chunkSize, f);

	return dataBuffer;
}

void DecimaArchive::decompressChunkData(DataBuffer data, uint64_t decompressedSize, unsigned char *output) {
	Kraken_Decompress(&data[0], data.size(), output, decompressedSize);
}

uint32_t DecimaArchive::getFileEntryIndex(int id) {
	for (int i = 0; i < fileTable.size(); i++) {
		if (fileTable[i].entryNum == id)
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
		decompressChunkData(getChunkData(chunkTable[i]), chunkTable[i].uncompressedSize, &tempBuffer[pos]);
		pos += chunkTable[i].uncompressedSize;
	}

	uint64_t filePosition = fileOffset % header.maxChunkSize;

	DataBuffer file(fileSize);

	memcpy(&file[0], &tempBuffer[filePosition], fileSize);

	return file;

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

	parseFileTable(f, header.fileTableCount);
	parseChunkTable(f, header.chunkTableCount);
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
