#pragma once
#include "../decima/file/prefetch/CorePrefetch.h"
#include "../decima/archive/mpk/ArchiveMoviePack.h"
#include "../decima/archive/bin/initial/BinInitial.h"

typedef enum CLI_COMMAND {
	LIST,
	EXTRACT,
	REPACK
} CLI_COMMAND;

struct argcRange {
	uint8_t low;
	uint8_t high;
};

class CLI {
public:
	CLI(int argc, char **argv);
	~CLI();

	void run(const char* programName, const char* version);
	void exit();
private:

	int argc;
	char **argv;

	const char *USAGE_MESSAGE = "Usage:\t DecimaExplorer.exe [-e/-extract] inputfile fileid outputfile \n"
								"\t DecimaExplorer.exe [-e/-extract] inputfile filename outputfile\n"
								"\t DecimaExplorer.exe [-e/-extract] [directory containing data files] filename outputfile\n"
								"\t DecimaExplorer.exe [-e/-extract] [directory containing data files] filename\n"
								"\t DecimaExplorer.exe [-l/-list] [directory containing data files]\n"
								"Available Options:\n"
								"\tList:    -l, -list\n"
								"\tExtract: -e, -extract\n";

	const char *EXIT_MESSAGE  = "Exiting\n";

	//command methods
	void extract(char* arg);
	void repack();
	void list();

	//cli methods
	void printUsage();
	bool checkInput();
	bool isNumber(char* arg);
	bool isCommand(char* arg);
	std::string setupOutput();
	int argToNumber(char* arg);
	void fileExtract(char* arg);
	void directoryExtract(char* arg);
	CLI_COMMAND argToCommand(char* arg);
	argcRange getArgCount(CLI_COMMAND command);
	void processCommand(CLI_COMMAND command, char* arg);
	void archiveExtract(char* arg, DecimaArchive* archive);
	void removeHashes(const std::vector<std::string>& fileList, const char* dataFolder);
};