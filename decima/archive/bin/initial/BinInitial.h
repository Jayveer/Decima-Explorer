#pragma once
#include "../ArchiveBin.h"

class BinInitial : public ArchiveBin {
protected:
	std::string filename = "initial";
	std::string filehash = "7017f9bb9d52fc1c4433599203cc51b1";

	const char* NOTFOUNDERROR  = "Failed to find initial archive";

public:
	BinInitial(std::string directory);
	~BinInitial();

	int open() override;
	inline std::string getFileHash() { return this->filehash; }
	inline void setFileHash(std::string filehash) { this->filehash = filehash; }
};