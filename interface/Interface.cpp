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


struct BinFileEntryNumSorter {
    inline bool operator() (const BinFileEntry& s1, const BinFileEntry& s2) {
        return (s1.entryNum < s2.entryNum);
    }
};

void Interface::extractFileMap(const char* fileDirectory) {
	std::ofstream out("file_hash.txt", std::ios::binary);
	const char* newLine = "\r\n";
	char buf[1024];

	std::vector<std::string> availableFiles = getFilesFromDirectory(fileDirectory, ".bin");

    int count = 0;
	for (int i = 0; i < availableFiles.size(); i++) {
		const char* str = availableFiles[i].c_str();
		uint32_t size = availableFiles[i].size();

		out.write(str, size);
		out.write(newLine, 2);

		ArchiveBin decimaArchive(str);
		//decimaArchive.setMessageHandler(this);
		if (!decimaArchive.open()) continue;
		std::vector <BinFileEntry> fileTable = decimaArchive.getFileTable();
		std::sort(fileTable.begin(), fileTable.end(), BinFileEntryNumSorter());

		for (int j = 0; j < fileTable.size(); j++) {
			snprintf(buf, sizeof(buf), "- %i: %08x%08x", fileTable[j].entryNum, (uint32_t)(fileTable[j].hash >> 32), (uint32_t)(fileTable[j].hash));
			out.write(buf, strlen(buf));
			out.write(newLine, 2);
		}
		count += fileTable.size();
		out.write(newLine, 2);
	}

	out.write(newLine, 2);
	snprintf(buf, sizeof(buf), "total: %i", count);
	out.write(buf, strlen(buf));
	out.write(newLine, 2);
}


const char* Interface::getContainingBinFile(const char* filename) {
	std::string fname = filename;
	if (!hasExtension(fname)) addExtension(fname, "core");
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

int Interface::directoryExtract(const char* filename, std::string output) {
	const char* binFile = getContainingBinFile(filename);
	if (binFile == NULL) return 0;
	setupOutput(output);
	int done = extract(binFile, filename, output.c_str());
	return done;
}

int Interface::fileListExtract(const char* fileList) {
	int count = 0;

	std::ifstream infile(fileList);

	std::string line;
	while (std::getline(infile, line)) {
        if (line.empty())
			continue;
		if (line.rfind("#", 0) == 0) //skip comments
			continue;
		count += directoryExtract(line.c_str(), line);
	}

	return count;
}

void Interface::batchExtract(const std::vector<char*>& filenames, std::string output, int batchSize, int batchOffset) {
	int step = batchSize < 10 ? 1 : batchSize / 10;

	for (int i = batchOffset; i < batchSize + batchOffset; i++) {
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

void destroyArchive(DecimaArchive* archive, const char* archiveFile) {
	const char* ext = getFileExtension(archiveFile).c_str();
	if (ext == "mpk") {
		return delete (ArchiveMoviePack*)archive;
	}

	return delete (ArchiveBin*)archive;
}

int Interface::extract(const char* archiveFile, int id, const char* output) {
	DecimaArchive* archive = archiveFactory(archiveFile);
	archive->setMessageHandler(this);
	if (!archive->open()) {
		destroyArchive(archive, archiveFile);
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
		destroyArchive(archive, archiveFile);
		return 0;
	}

	archive->extractFile(input, output);
	destroyArchive(archive, archiveFile);
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

void Interface::swap(const char* dataDir, const char* swapFile) {
	std::vector<Swapper> swapMap;
	std::ifstream file(swapFile);
	std::string str;
	while (std::getline(file, str)) {
		Swapper map;
		const char* regex = "([^\\s]+)(\\s+)?->(\\s+)?([^\\s]+)";
		std::regex re(regex);
		std::smatch match;

		if (std::regex_search(str, match, re)) {
			map.firstFile = match[1];
			map.secondFile = match[4];
			swapMap.push_back(map);
		}
	}

	std::vector<std::string> files = getFilesFromDirectory(dataDir, ".bin");
	for (int i = 0; i < files.size(); i++) {
		ArchiveBin decimaArchive(files[i]);
		decimaArchive.setMessageHandler(this);
		decimaArchive.open();
		decimaArchive.swapEntries(swapMap);
	}
}