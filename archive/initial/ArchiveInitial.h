#pragma once
#include "../DecimaArchive.h"

class ArchiveInitial : public DecimaArchive {
	std::string filename = "initial.bin";
	std::string filehash = "7017f9bb9d52fc1c4433599203cc51b1.bin";

public:
	ArchiveInitial(std::string directory);
	~ArchiveInitial();

	int open() override;
	inline std::string getFileHash() { return this->filehash; }
	inline void setFileHash(std::string filehash) { this->filehash = filehash; }
};