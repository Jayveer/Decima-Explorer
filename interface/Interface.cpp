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

bool Interface::getFinalFilename(const char* filename, std::string& p_binName, std::string& p_fname) {
	const int max_extensions = 6;
	const char* extensions[max_extensions] = {"core", "stream", "core.stream", "coretext", "coredebug", "dep"};

	// try default name first
	std::string fname = filename;
	const char* binFile = getContainingBinFile(fname);
	if (binFile != NULL) {
		p_binName = binFile;
		p_fname = fname;
		return true;
	}

	// try common extensions (files like .soundbank.core exists in prefetch list so extension check isn't good)
	for (int i = 0; i < max_extensions; i++) {
		fname = filename;
		addExtension(fname, extensions[i]);

		binFile = getContainingBinFile(fname);
		if (binFile != NULL) {
			p_binName = binFile;
			p_fname = fname;
			return true;
		}
	}

	p_binName = "";
	p_fname = "";
	return false;
}


struct BinFileEntryNumSorter {
    inline bool operator() (const BinFileEntry& s1, const BinFileEntry& s2) {
        return (s1.entryNum < s2.entryNum);
    }
};

bool Interface::loadHashNames(const char* fileDirectory, std::unordered_map<uint64_t, std::string>& hashNames) {
	const char* fileList = "filenames-all.txt";
	if (!checkFileExists(fileList))
		return false;

	buildFileMap(fileDirectory);

	std::ifstream infile(fileList);

	std::string binFile;
	std::string fname;
	std::string line;
	while (std::getline(infile, line)) {
        if (line.empty())
			continue;
		if (line.rfind("#", 0) == 0) //skip comments
			continue;

		if (!getFinalFilename(line.c_str(), binFile, fname))
			continue;

		uint64_t hash = getFileHash(fname);
		hashNames[hash] = fname;
	}

	return true;
}

void Interface::extractFileMap(const char* fileDirectory) {
	std::ofstream out("file_hash.txt", std::ios::binary);
	const char* newLine = "\r\n";
	char buf[1024];

	// get names if possible
	std::unordered_map<uint64_t, std::string> hashNames;
	loadHashNames(fileDirectory, hashNames);

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
			uint32_t entryNum = fileTable[j].entryNum;
			uint64_t hash = fileTable[j].hash;

			bool found = hashNames.find(hash) != hashNames.end();
			if (found) {
				std::string fname = hashNames[hash];
				snprintf(buf, sizeof(buf), "- %i: %08x%08x = %s", entryNum, (uint32_t)(hash >> 32), (uint32_t)(hash), fname.c_str());
			}
			else {
				snprintf(buf, sizeof(buf), "- %i: %08x%08x", entryNum, (uint32_t)(hash >> 32), (uint32_t)(hash));
			}
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


const char* Interface::getContainingBinFile(const std::string& filename) {
	uint64_t hash = getFileHash(filename);
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

int Interface::directoryExtract(const char* filename, const char* output) {
	std::string binFile;
	std::string fname;
	if (!getFinalFilename(filename, binFile, fname))
		return 0;

	if (output == NULL)
		output = fname.c_str();

	setupOutput(output);
	int done = extract(binFile.c_str(), fname.c_str(), output);
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
		count += directoryExtract(line.c_str(), NULL);
	}

	return count;
}

void Interface::batchExtract(const std::vector<char*>& filenames, std::string output, int batchSize, int batchOffset) {
	int step = batchSize < 10 ? 1 : batchSize / 10;

	for (int i = batchOffset; i < batchSize + batchOffset; i++) {
		std::string newOutput = addFileToPath(filenames[i], output); //todo fix output name
		directoryExtract(filenames[i], newOutput.c_str());
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
	std::string ext = getFileExtension(archiveFile);
	if (ext == "mpk") {
		std::cout << "archive movie pack\n";
		return new ArchiveMoviePack(archiveFile);
	}

	return new ArchiveBin(archiveFile);
}

void destroyArchive(DecimaArchive* archive, const char* archiveFile) {
	std::string ext = getFileExtension(archiveFile);
	if (ext == "mpk") {
		return delete (ArchiveMoviePack*)archive;
	}

	return delete (ArchiveBin*)archive;
}

int Interface::extractAllIds(const char* archiveFile) {
	DecimaArchive* archive = archiveFactory(archiveFile);
	archive->setMessageHandler(this);
	if (!archive->open()) {
		destroyArchive(archive, archiveFile);
		return 0;
	}

	std::string path = getBaseFile(archiveFile);

	createDirectoriesFromPath(path);
	int id = 0;
	char buf[1024];
	while (true) {
		snprintf(buf, sizeof(buf), "%s/%06i", path.c_str(), id);
		//std::cout << buf <<"\n";

		int ret = archive->extractFile(id, buf);
		if (ret <= 0)
			break;
		id++;
	}
	delete archive;
	return id;
}

int Interface::extract(const char* archiveFile, int id, const char* output) {
	DecimaArchive* archive = archiveFactory(archiveFile);
	archive->setMessageHandler(this);
	if (!archive->open()) {
		destroyArchive(archive, archiveFile);
		return 0;
	}
	int ret = archive->extractFile(id, output);
	delete archive;
	return ret;
}

int Interface::extract(const char* archiveFile, const char* input, const char* output) {
	DecimaArchive* archive = archiveFactory(archiveFile);
	archive->setMessageHandler(this);
	if (!archive->open()) {
		destroyArchive(archive, archiveFile);
		return 0;
	}

	int ret = archive->extractFile(input, output);
	destroyArchive(archive, archiveFile);
	return ret;
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