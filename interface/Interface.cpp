#include "Interface.h"

Interface::Interface()
{
}

Interface::~Interface()
{
}

void Interface::repack(const std::string& filename, const std::string& directory) {
	std::vector<std::string> files;
	traverseDirectory(directory, "*", files);
	ArchiveBin decimaArchive(filename);
	if (!decimaArchive.open()) return;
	decimaArchive.update(directory, files);
}

void Interface::pack(const std::string& filename, const std::string& directory) {
	std::vector<std::string> files;
	traverseDirectory(directory, "*", files);
	ArchiveBin decimaArchive(filename);
	decimaArchive.create(directory, files);
}