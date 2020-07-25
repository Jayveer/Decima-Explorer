#pragma once
#include <string>
#include <vector>
#include "../DecimaArchive.h"

typedef struct ArchiveMoviePackHeader {
	uint32_t magic;
	uint32_t key;
	uint32_t tableCount;
	uint32_t dataOffset;
} DecimaMoviePackHeader;

typedef struct ArchiveMoviePackFileEntry {
	uint64_t hash;
	uint32_t key;
	uint32_t key2;
	uint64_t size;
	uint64_t offset;
} ArchiveMoviePackFileEntry;

class ArchiveMoviePack : public DecimaArchive {
private:
	std::string extension = ".mpk";
	ArchiveMoviePackHeader header = { 0 };
	std::vector<ArchiveMoviePackFileEntry> fileTable;

	uint32_t saltA[4] = { 0x833237C3, 0xBA5CD4B6, 0x3371A06B, 0xAEA7EDB2 };

	bool checkMagic() override;
	uint32_t getMagic() override;

	void parseHeader(FILE* f) override;
	void parseFileTable(FILE* f);
public:
	ArchiveMoviePack(std::string filename);
	~ArchiveMoviePack();
	int open() override;
};

