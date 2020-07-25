#include "ArchiveMoviePack.h"

ArchiveMoviePack::ArchiveMoviePack(std::string filename): DecimaArchive(filename, this->extension) {
	setSaltA(this->saltA);
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