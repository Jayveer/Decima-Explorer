#pragma once

#include "../ooz/Kraken.h"
#include <inttypes.h>
#include <vector>

typedef struct DecimaHeader {
	uint32_t magic; //0x20304050
	uint32_t version; //0x3D
	uint64_t fileSize;
	uint64_t dataSize;
	uint64_t fileTableCount;
	uint32_t chunkTableCount;
	uint32_t maxChunkSize;
} DecimaHeader;

typedef struct DecimaFileEntry {
	uint32_t entryNum;
	uint32_t unknown;
	uint64_t unknown2; //maybe file hash, not sure
	uint64_t offset;
	uint32_t size;
	uint32_t unknown3;
} DecimaFileTable;

typedef struct DecimaChunkEntry {
	uint64_t uncompressedOffset; //relative offset once uncompressed
	uint32_t uncompressedSize;
	uint32_t unknown;
	uint64_t compressedOffset;
	uint32_t compressedSize;
	uint32_t unknown2;
} DecimaChunkTable;

typedef std::vector<uint8_t> DataBuffer;

class DecimaArchive {
private:
	DecimaHeader header;
	std::vector<DecimaFileEntry>  fileTable;
	std::vector<DecimaChunkEntry> chunkTable;

	std::string filename;

	void parseHeader(FILE* file);
	void parseFileTable(FILE* f, uint64_t fileTableCount);
	void parseChunkTable(FILE* f, uint64_t chunkTableCount);

	bool checkMagic();
	uint32_t getFileEntryIndex(int id);
	DecimaFileEntry getFileEntry(int id);
	void setFilename(std::string filename);
	int findChunkWithOffset(uint64_t offset);
	DataBuffer extract(DecimaFileEntry fileEntry);
	DataBuffer getChunkData(DecimaChunkEntry chunkEntry);
	int calculateChunkTableOffset(uint64_t fileTableCount);
	int writeDataToFile(DataBuffer data, std::string filename);
	uint64_t calculateFirstContainingChunk(uint64_t fileOffset, int chunkSize);
	uint64_t calculateLastContainingChunk(uint64_t fileOffset, int fileSize, int chunkSize);
	void decompressChunkData(DataBuffer data, uint64_t decompressedSize, unsigned char *output);

public:
	~DecimaArchive();
	DecimaArchive(std::string filename);

	int open();
	int getVersion();
	std::string getFilename();
	int extractFile(uint32_t id, std::string output);
	
};
