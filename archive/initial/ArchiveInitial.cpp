#include "ArchiveInitial.h"
#include "ArchiveInitialError.h"

ArchiveInitial::ArchiveInitial(std::string directory) {
	setFilename(addFileToPath(this->filename, directory));
	setFileHash(addFileToPath(this->filehash, directory));
}

ArchiveInitial::~ArchiveInitial() {

}

int ArchiveInitial::open() {
	bool check = checkFileExists(getFilename());
	
	if (!check) {
		check = checkFileExists(getFileHash());
		if (!check) {
			showError(NOTFOUND);
			return 0;
		}
		setFilename(getFileHash());
	}

	DecimaArchive::open();
	return 1;
}