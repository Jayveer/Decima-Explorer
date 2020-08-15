#pragma once
#include "../DecimaArchive.h"
#include "ArchiveBinError.h"

typedef struct BinHeader {
	uint32_t magic;
	uint32_t key;
	uint64_t fileSize;
	uint64_t dataSize;
	uint64_t fileTableCount;
	uint32_t chunkTableCount;
	uint32_t maxChunkSize;
} BinHeader;

typedef struct BinFileEntry {
	uint32_t entryNum;
	uint32_t key;
	uint64_t hash;
	uint64_t offset;
	uint32_t size;
	uint32_t key2;
} BinFileEntry;

typedef struct BinChunkEntry {
	uint64_t uncompressedOffset;
	uint32_t uncompressedSize;
	uint32_t key;
	uint64_t compressedOffset;
	uint32_t compressedSize;
	uint32_t key2;
} BinChunkEntry;

typedef std::vector<uint8_t> DataBuffer;

class ArchiveBin : public DecimaArchive {
private:
	BinHeader header = {0};
	std::vector<BinFileEntry>  fileTable;
	std::vector<BinChunkEntry> chunkTable;

	uint32_t murmurSalt[4]  = { 0x0FA3A9443, 0x0F41CAB62, 0x0F376811C, 0x0D2A89E3E };
	uint32_t murmurSalt2[4] = { 0x06C084A37, 0x07E159D95, 0x03D5AF7E8, 0x018AA7D3F };

	void parseHeader(FILE* file) override;
	void parseFileTable(FILE* f, uint64_t fileTableCount);
	void parseChunkTable(FILE* f, uint64_t chunkTableCount);

	bool checkMagic() override;
	void decryptHeader();
	void decryptFileTable();
	void decryptChunkTable();
	uint32_t getFileEntryIndex(int id);
	BinFileEntry getFileEntry(int id);
	int findChunkWithOffset(uint64_t offset);
	DataBuffer extract(BinFileEntry fileEntry);
	uint32_t getFileEntryIndex(const std::string& filename);
	void decryptChunkData(int32_t id, DataBuffer* data);
	DataBuffer getChunkData(BinChunkEntry chunkEntry);
	int calculateChunkTableOffset(uint64_t fileTableCount);

	uint64_t calculateFirstContainingChunk(uint64_t fileOffset, int chunkSize);
	uint64_t calculateLastContainingChunk(uint64_t fileOffset, int fileSize, int chunkSize);
	void decompressChunkData(const DataBuffer& data, uint64_t decompressedSize, unsigned char* output);

protected:
	uint32_t getMagic() override;
	std::string extension = ".bin";
public:
	~ArchiveBin();
	ArchiveBin(std::string filename);

	int open() override;
	int create(const std::string& basePath, const std::vector<std::string>& fileList);
	DataBuffer extractFile(std::string filename);
	int extractFile(uint32_t id, std::string output);
	int extractFile(std::string filename, std::string output, bool suppressError = 0);

	const std::vector<BinFileEntry>& getFileTable() { return fileTable; }

};