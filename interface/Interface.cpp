#include "Interface.h"

Interface::Interface() {
	progressMutex = new std::mutex();
}

Interface::~Interface() {
	delete progressMutex;
}

void Interface::updateProgress(int count) {
	progressMutex->lock();
	this->progressNum += count;
	progressMutex->unlock();
}

int32_t Interface::getProgress() {
	progressMutex->lock();
	int32_t pNum = progressNum;
	progressMutex->unlock();
	return pNum;
}

void Interface::buildFileMap(const char* fileDirectory) {
	availableFiles = getFilesFromDirectory(fileDirectory, ".bin");

	for (int i = 0; i < availableFiles.size(); i++) {
		ArchiveBin decimaArchive(availableFiles[i].c_str());
		decimaArchive.setMessageHandler(this);
		if (!decimaArchive.open()) continue;

		std::vector <BinFileEntry> fileTable = decimaArchive.getFileTable();

		for (int j = 0; j < fileTable.size(); j++) {
			fileMap[fileTable[j].hash] = availableFiles[i].c_str();
		}
	}
}

const char* Interface::getContainingBinFile(const char* filename) {
	std::string fname = filename;
	if (!hasExtension(fname, "core")) addExtension(fname, "core");
	uint64_t hash = getFileHash(fname);
	return fileMap[hash];
}

//TODO make dedicated thread handler class
void Interface::parallelExtract(const std::string& directory, const std::vector<char*>& selectedStrings) {
	uint32_t numThreads = std::thread::hardware_concurrency();
	if (!numThreads) numThreads = 2;

	uint32_t divvy = selectedStrings.size() / numThreads;
	uint32_t excess = selectedStrings.size() % numThreads;
	uint16_t add = 0;

	if (!divvy) numThreads = excess;

	std::vector<std::future<void>> futures;

	for (int i = 0; i < numThreads; i++) {
		int batchSize = divvy;
		int batchOffset = i * divvy;

		if (i < excess) batchSize++;

		futures.push_back(std::async(std::launch::async, &Interface::batchExtract, this, std::ref(selectedStrings), std::ref(directory), batchSize, batchOffset + add));
		if (i < excess) add++;
	}

	int x = 0;
	for (int i = 0; i < futures.size(); i++) {
		while (!futures[i]._Is_ready()) {
			if (x % 10000 == 0) intervalUpdate();
			update();
			x++;
		}
		intervalUpdate();
	}

	if (this->forceQuit) exit();
}

void Interface::setupOutput(const std::string& output) {
	std::string path = getFilePathWithoutName(output);
	if (path != "") createDirectoriesFromPath(path);
}

void Interface::directoryExtract(const char* filename, std::string output) {
	const char* binFile = getContainingBinFile(filename);
	if (binFile == NULL) return;
	setupOutput(output);
	extract(binFile, filename, output.c_str());
}

void Interface::batchExtract(const std::vector<char*>& filenames, std::string output, int batchSize, int batchOffset) {
	int step = batchSize < 10 ? 1 : batchSize / 10;

	for (int i = batchOffset; i < batchSize + batchOffset; i++) {
		//std::string newOutput = output == "" ? filenames[i] : output + "\\/" + filenames[i];
		std::string newOutput = addFileToPath(filenames[i], output);
		directoryExtract(filenames[i], newOutput);
		if ((i - batchOffset) % step == 0) updateProgress(step);
		if (this->forceQuit) return;
	}
	if (step != 1) updateProgress(batchSize % 10);
}

int Interface::initPrefetch(const char* binFile) {
	BinInitial initial(binFile);
	initial.setMessageHandler(this);
	if (!initial.open()) return 0;
	DataBuffer data = initial.extractFile(prefetchFile.getFilename());
	if (data.empty()) return 0;
	prefetchFile.open(data);
	return 1;
}

void Interface::deinitPrefetch() {
	this->prefetchFile = {};
}

DecimaArchive* archiveFactory(const char* archiveFile) {
	const char* ext = getFileExtension(archiveFile).c_str();
	if (ext == "mpk") {
		return new ArchiveMoviePack(archiveFile);
	}

	return new ArchiveBin(archiveFile);
}

void destroyArchive(DecimaArchive* archive) {
	delete archive;
}

int Interface::extract(const char* archiveFile, int id, const char* output) {
	DecimaArchive* archive = archiveFactory(archiveFile);
	archive->setMessageHandler(this);
	if (!archive->open()) {
		destroyArchive(archive);
		return 0;
	}
	archive->extractFile(id, output);
	delete archive;
	return 1;
}

int Interface::extract(const char* archiveFile, const char* input, const char* output) {
	DecimaArchive* archive = archiveFactory(archiveFile);
	archive->setMessageHandler(this);
	if (!archive->open()) {
		destroyArchive(archive);
		return 0;
	}

	archive->extractFile(input, output);
	destroyArchive(archive);
	return 1;
}

std::vector<std::string> Interface::getFiles(const std::string& directory) {
	std::vector<std::string> files;
	traverseDirectory(directory, "*", files);
	return files;
}

void Interface::repack(const std::vector<std::string> files, const std::string& filename, const std::string& directory) {
	ArchiveBin decimaArchive(filename);
	decimaArchive.setMessageHandler(this);
	if (!decimaArchive.open()) return;
	decimaArchive.update(directory, files);
}

void Interface::pack(const std::vector<std::string> files, const std::string& directory, const std::string& filename) {
	ArchiveBin decimaArchive(filename);
	decimaArchive.setMessageHandler(this);
	decimaArchive.create(directory, files);
}
