#pragma once
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

	const uint64_t MAXSTREAM = 0x100000;
	const std::string extension = ".mpk";
	ArchiveMoviePackHeader header = { 0 };
	std::vector<ArchiveMoviePackFileEntry> fileTable;

	uint32_t saltA[4] = { 0x833237C3, 0xBA5CD4B6, 0x3371A06B, 0xAEA7EDB2 };
	uint32_t saltB[4] = { 0xCE857276, 0x9ACC40E8, 0x8242DBD6, 0xCF703987, };

	bool checkMagic() override;
	uint32_t getMagic() override;

	void parseHeader(FILE* f) override;
	void parseFileTable(FILE* f);

	uint32_t getFileEntryIndex(std::string filename);
	void saveStream(FILE* input, FILE* output, uint64_t size, uint32_t* key, uint64_t pass);
	void extract(ArchiveMoviePackFileEntry fileEntry, std::string output);
public:
	ArchiveMoviePack(std::string filename);
	~ArchiveMoviePack();
	int open() override;
	int extractFile(uint32_t id, const char* output);
	int extractFile(std::string filename, const char* output, bool suppressError = 0);
};