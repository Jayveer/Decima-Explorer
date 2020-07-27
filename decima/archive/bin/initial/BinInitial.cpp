#include "BinInitial.h"


BinInitial::BinInitial(std::string directory) : ArchiveBin(this->filename) {
	setFilename(addFileToPath(this->filename, directory) + this->extension);
	setFileHash(addFileToPath(this->filehash, directory) + this->extension);
}

BinInitial::~BinInitial() {

}

int BinInitial::open() {
	bool check = checkFileExists(getFilename());
	
	if (!check) {
		check = checkFileExists(getFileHash());
		if (!check) {
			showError(NOTFOUND);
			return 0;
		}
		setFilename(getFileHash());
	}

	ArchiveBin::open();
	return 1;
}