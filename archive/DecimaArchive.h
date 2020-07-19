#pragma once

#include "../ooz/Kraken.h"
#include "../hash/md5.h"
#include "../hash/MurmurHash3.h"
#include <string>
#include <inttypes.h>
#include <vector>

typedef struct DecimaHeader {
	uint32_t magic; //0x20304050
	uint32_t key;
	uint64_t fileSize;
	uint64_t dataSize;
	uint64_t fileTableCount;
	uint32_t chunkTableCount;
	uint32_t maxChunkSize;
} DecimaHeader;

typedef struct DecimaFileEntry {
	uint32_t entryNum;
	uint32_t key;
	uint64_t hash;
	uint64_t offset;
	uint32_t size;
	uint32_t key2;
} DecimaFileTable;

typedef struct DecimaChunkEntry {
	uint64_t uncompressedOffset; //relative offset once uncompressed
	uint32_t uncompressedSize;
	uint32_t key;
	uint64_t compressedOffset;
	uint32_t compressedSize;
	uint32_t key2;
} DecimaChunkTable;

typedef std::vector<uint8_t> DataBuffer;

class DecimaArchive {
private:
	DecimaHeader header;
	std::vector<DecimaFileEntry>  fileTable;
	std::vector<DecimaChunkEntry> chunkTable;

	std::string filename;

	uint8_t seed = 0x2A;
	uint32_t murmurSalt[4]  = { 0x0FA3A9443, 0x0F41CAB62, 0x0F376811C, 0x0D2A89E3E };
	uint32_t murmurSalt2[4] = { 0x06C084A37, 0x07E159D95, 0x03D5AF7E8, 0x018AA7D3F };

	void parseHeader(FILE* file);
	void parseFileTable(FILE* f, uint64_t fileTableCount);
	void parseChunkTable(FILE* f, uint64_t chunkTableCount);

	bool checkMagic();
	bool isEncrypted();
	void decryptHeader();
	void decryptFileTable();
	void decryptChunkTable();
	uint32_t getFileEntryIndex(int id);
	DecimaFileEntry getFileEntry(int id);
	void setFilename(std::string filename);
	int findChunkWithOffset(uint64_t offset);
	DataBuffer extract(DecimaFileEntry fileEntry);
	void decryptChunkData(int32_t id, DataBuffer* data);
	DataBuffer getChunkData(DecimaChunkEntry chunkEntry);
	int calculateChunkTableOffset(uint64_t fileTableCount);
	void cipher(uint32_t key, uint32_t key2, uint32_t* src);
	void dataCipher(uint32_t chunkID, uint8_t* src, int size);
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
