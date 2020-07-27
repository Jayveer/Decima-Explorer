#include "ArchiveMoviePack.h"

ArchiveMoviePack::ArchiveMoviePack(std::string filename): DecimaArchive(filename, this->extension) {
	setSaltA(this->saltA);
	setSaltB(this->saltB);
}

ArchiveMoviePack::~ArchiveMoviePack() {
}

bool ArchiveMoviePack::checkMagic() {
	return (header.magic == 0x01000D0A);
}

uint32_t ArchiveMoviePack::getMagic() {
	return header.magic;
}

int ArchiveMoviePack::open() {
	FILE* f;
	fopen_s(&f, getFilename().c_str(), "rb");
	parseHeader(f);
	parseFileTable(f);

	return 1;
}

uint32_t ArchiveMoviePack::getFileEntryIndex(std::string filename) {
	uint64_t hash = getFileHash(filename);
	for (int i = 0; i < fileTable.size(); i++) {
		if (fileTable[i].hash == hash)
			return i;
	}
	return -1;
}

int ArchiveMoviePack::extractFile(uint32_t id, std::string output) {
	if (id < 0 || id >= fileTable.size()) {
		showError(FINDINDEXFAIL);
		return 0;
	}

	extract(fileTable[id], output);

	return 1;
}

int ArchiveMoviePack::extractFile(std::string filename, std::string output, bool suppressError) {
	uint32_t i = getFileEntryIndex(filename);

	if (i == -1) {
		if (!suppressError) showError(INVALIDFILENAME);
		return 0;
	}

	extract(fileTable[i], output);

	return 1;
}

void ArchiveMoviePack::extract(ArchiveMoviePackFileEntry fileEntry, std::string output) {
	uint32_t* key = (uint32_t*)&fileEntry;
	uint64_t numPasses = fileEntry.size / 0x100000;
	uint64_t remainder = fileEntry.size % 0x100000;

	FILE* fo;
	fopen_s(&fo, output.c_str(), "wb");

	FILE* f;
	fopen_s(&f, getFilename().c_str(), "rb");

	_fseeki64(f, fileEntry.offset, SEEK_SET);

	for (int i = 0; i < numPasses; i++) {
		saveStream(f, fo, MAXSTREAM, key, i);
	}

	saveStream(f, fo, remainder, key, numPasses);

	fclose(f);
	fclose(fo);
}


void ArchiveMoviePack::saveStream(FILE* input, FILE* output, uint64_t size, uint32_t* key, uint64_t pass) {
	uint8_t* data = new uint8_t[size];
	fread(data, size, 1, input);
	if (isEncrypted()) movieDecrypt(key, data, size, pass);
	fwrite(data, size, 1, output);
	delete[] data;
}

void ArchiveMoviePack::parseHeader(FILE* f) {
	fread(&header.magic, 4, 1, f);
	fread(&header.key, 4, 1, f);
	fread(&header.tableCount, 4, 1, f);
	fread(&header.dataOffset, 4, 1, f);
	if (isEncrypted()) decrypt(header.key, (uint32_t*)&header);
}

void ArchiveMoviePack::parseFileTable(FILE* f) {
	for (int i = 0; i < header.tableCount; i++) {
		uint32_t key, key2;
		ArchiveMoviePackFileEntry fileEntry;

		fread(&fileEntry.hash, 8, 1, f);
		fread(&key, 4, 1, f);
		fread(&key2, 4, 1, f);
		fread(&fileEntry.size, 8, 1, f);
		fread(&fileEntry.offset, 8, 1, f);

		if (isEncrypted()) decrypt(key, key2, (uint32_t*)&fileEntry);
		fileEntry.key = key;
		fileEntry.key2 = key2;
		fileTable.push_back(fileEntry);
	}
}