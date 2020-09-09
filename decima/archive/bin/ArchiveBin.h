#pragma once

#include "../DecimaArchive.h"

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

	void updateHeader();
	void updateFileTable();
	void updateChunkTable();

	void addChunkData(std::vector<DataBuffer>& chunks);
	void addChunkTable(const std::vector<DataBuffer>& chunks);

	void writeHeader(FILE* f);
	void writeFileTable(FILE* f);
	void writeChunkTable(FILE* f);
	void writeChunkData(FILE* f, const std::vector<DataBuffer>& chunks);

	bool checkMagic() override;
	void decryptHeader();
	void decryptFileTable();
	void decryptChunkTable();
	BinFileEntry getFileEntry(int id);
	uint32_t getFileEntryIndex(int id);
	int findChunkWithOffset(uint64_t offset);
	int nukeHash(const std::string& filename);
	DataBuffer extract(BinFileEntry fileEntry);
	DataBuffer getChunkData(BinChunkEntry chunkEntry);
	void decryptChunkData(int32_t id, DataBuffer* data);
	uint32_t getFileEntryIndex(const std::string& filename);


	uint64_t calculateDataOffset();
	uint64_t getUncompressedSizeEnd();
	uint64_t calculateFileTableSize();
	uint64_t calculateChunkTableSize();
	uint64_t calculateChunkTableOffset();
	uint64_t calculateDataOffset(uint64_t numChunks);
	uint64_t calculateChunkTableSize(uint64_t numChunks);
	uint64_t calculateFirstContainingChunk(uint64_t fileOffset, int chunkSize);
	std::vector<DataBuffer> createChunkEntries(DataBuffer& buffer, bool isUpdate);
	uint64_t calculateLastContainingChunk(uint64_t fileOffset, int fileSize, int chunkSize);
	int compressChunkData(unsigned char* input, uint64_t decompressedSize, DataBuffer& output);
	void decompressChunkData(DataBuffer& data, uint64_t decompressedSize, unsigned char* output);
	DataBuffer createFileEntries(const std::string& basePath, const std::vector<std::string>& fileList, bool isUpdate);

protected:
	uint32_t getMagic() override;
	std::string extension = ".bin";

	const char* INVALIDMAGICERROR = "Input file is of an unrecognized format";
	const char* COMPRESSFAILERROR = "Failed to compress data, please make sure you have a version of oo2core DLL in the same directory as Decima Explorer";
	const char* DECOMPRESSFAILERROR = "Failed to decompress data, try adding a version of oo2core DLL in the same directory as Decima Explorer for this file";
	const char* PARSEFILETABLEFAILERROR = "Failed to parse file table";
	const char* PARSECHUNKTABLEFAILERROR = "Failed to parse chunk table";
public:
	~ArchiveBin();
	ArchiveBin(std::string filename);

	int open() override;
	DataBuffer extractFile(std::string filename);
	int extractFile(uint32_t id, std::string output);
	void swapEntries(const std::vector<Swapper>& swapMap);
	void nukeHashes(const std::vector<std::string>& fileList);
	int extractFile(std::string filename, std::string output, bool suppressError = 0);
	int create(const std::string& basePath, const std::vector<std::string>& fileList);
	int update(const std::string& basePath, const std::vector<std::string>& fileList);
	const std::vector<BinFileEntry>& getFileTable() { return fileTable; }

};