#pragma once
#include <thread>

#include "../../ooz/Kraken.h"
#include "../../hash/md5.h"

#include "../../utils/Fileutils.h"
#include "../common/util.h"
#include "DecimaArchiveError.h"

typedef std::vector<uint8_t> DataBuffer;

class DecimaArchive {
private:	
	std::string filename;
	std::string extension;

	uint32_t saltA[4] = { 0x0FA3A9443, 0x0F41CAB62, 0x0F376811C, 0x0D2A89E3E };
	uint32_t saltB[4] = { 0x06C084A37, 0x07E159D95, 0x03D5AF7E8, 0x018AA7D3F };

protected:
	bool isEncrypted();
	void decrypt(uint32_t key, uint32_t* src);
	void decrypt(uint32_t key, uint32_t key2, uint32_t* src);
	int writeDataToFile(const DataBuffer& data, const std::string& filename);
	void dataDecrypt(uint32_t* key, uint8_t* src, int size);
	void movieDecrypt(uint32_t* key, uint8_t* src, int size, int pass);
	void setSaltA(uint32_t* salt);
	void setSaltB(uint32_t* salt);
	void setFilename(std::string Filename);

	virtual bool checkMagic() = 0;
	virtual uint32_t getMagic() = 0;
	virtual void parseHeader(FILE* file) = 0;	
	
public:
	~DecimaArchive();
	DecimaArchive(std::string filename, std::string extension);

	virtual int open() = 0;
	std::string getFilename();
	std::string getExtension();
	virtual int extractFile(uint32_t id, std::string output) = 0;
	virtual int extractFile(std::string filename, std::string output, bool suppressError = 0) = 0;
};
