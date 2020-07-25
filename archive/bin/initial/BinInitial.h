#pragma once
#include "../ArchiveBin.h"

class BinInitial : public ArchiveBin {
	std::string filename = "initial";
	std::string filehash = "7017f9bb9d52fc1c4433599203cc51b1";

public:
	BinInitial(std::string directory);
	~BinInitial();

	int open() override;
	inline std::string getFileHash() { return this->filehash; }
	inline void setFileHash(std::string filehash) { this->filehash = filehash; }
};