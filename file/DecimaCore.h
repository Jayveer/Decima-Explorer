#pragma once
#include <vector>
#include <string>
#include <fstream>
#include "../fileutils/fileutils.h"

typedef std::vector<uint8_t> DataBuffer;

class DecimaCore {
private:
	std::string filename;

protected:
	DecimaCore();
	virtual void parse(std::istream& f) = 0;
public:
	DecimaCore(std::string name);
	~DecimaCore();


	void open(DataBuffer data);
	void open(std::string filename);
	
	inline void setFilename(std::string filename) { this->filename = filename;  }
	inline std::string getFilename() { return this->filename; }
};