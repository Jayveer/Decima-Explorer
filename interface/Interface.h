#pragma once
#include <mutex>
#include <thread>
#include <future>
#include <regex>
#include <unordered_map>

#include "../decima/file/prefetch/CorePrefetch.h"
#include "../decima/archive/mpk/ArchiveMoviePack.h"
#include "../decima/archive/bin/initial/BinInitial.h"
#include "../utils/Arrayutils.h"
#include "../utils/NumUtils.h"
#include "../utils/Msgutils.h"

class Interface : public MessageHandler {
private:
	int32_t progressNum = 0;
	std::mutex* progressMutex;
	std::vector<std::string> availableFiles;
	

protected:
	CorePrefetch prefetchFile;
	std::unordered_map<uint64_t, const char*> fileMap;

	virtual void exit() = 0;
	virtual void update() = 0;
	virtual void intervalUpdate() = 0;
	virtual void run(std::string programName, std::string version) = 0;


	int32_t getProgress();
	bool forceQuit = false;

	void deinitPrefetch();
	void updateProgress(int count);
	int initPrefetch(const char* binFile);
	void setupOutput(const std::string& output);
	void buildFileMap(const char* fileDirectory);
	void extractFileMap(const char* fileDirectory);
	void swap(const char* dataDir, const char* swapFile);
	const char* getContainingBinFile(const char* filename);
	std::vector<std::string> getFiles(const std::string& directory);
	int directoryExtract(const char* filename, std::string output);
	int extract(const char* archiveFile, int id, const char* output);
	int extract(const char* archiveFile, const char* input, const char* output);
	void parallelExtract(const std::string& directory, const std::vector<char*>& selectedStrings);
	void batchExtract(const std::vector<char*>& filenames, std::string output, int batchSize, int batchOffset);
	void pack(const std::vector<std::string> files, const std::string& filename, const std::string& directory);
	void repack(const std::vector<std::string> files, const std::string& directory, const std::string& filename);

public:
	Interface();
	~Interface();
};