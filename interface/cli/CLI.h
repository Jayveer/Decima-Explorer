#pragma once

#include "../Interface.h"

typedef enum CLI_COMMAND {
	LIST,
	EXTRACT,
	PACK,
	REPACK,
	SWAP,
} CLI_COMMAND;

struct argcRange {
	uint8_t low;
	uint8_t high;
};

class CLI : public Interface {
public:
	CLI(int argc, char **argv);
	~CLI();

	void run (std::string programName, std::string version);
	void exit();
private:

	int argc;
	char **argv;

	const char *USAGE_MESSAGE = "Usage:\t DecimaExplorer.exe [-e/-extract] inputfile fileid outputfile \n"
								"\t DecimaExplorer.exe [-e/-extract] inputfile filename outputfile\n"
								"\t DecimaExplorer.exe [-e/-extract] [directory containing data files] filename outputfile\n"
								"\t DecimaExplorer.exe [-e/-extract] [directory containing data files] filename\n"
								"\t DecimaExplorer.exe [-r/-repack] [bin file to repack] [directory containing directories of core files]\n"
								"\t DecimaExplorer.exe [-p/-pack] [directory containing directories of core files] outputfile\n"
								"\t DecimaExplorer.exe [-s/-swap] [directory containing data files] [swap text file]\n"
								"\t DecimaExplorer.exe [-l/-list] [directory containing data files]\n"
								"Available Options:\n"
								"\tList:    \t-l, -list\n"
								"\tPack:	\t-p, -pack\n"
								"\tSwap:	\t-s, -swap\n"
								"\tRepack:	\t-r, -repack\n"
								"\tExtract: \t-e, -extract\n";

	const char *EXIT_MESSAGE  = "Exiting\n";

	//command methods
	void list();
	void cliSwap();
	void cliPack();
	void cliRepack();
	void cliExtract();

	void update();
	void intervalUpdate();

	void showError(const char* message);
	void showMessage(const char* message);
	void showWarning(const char* message);

	//cli methods
	void dirExtract();
	void printUsage();
	bool checkInput();
	void fileExtract();
	bool isNumber(char* arg);
	bool isCommand(char* arg);
	int argToNumber(char* arg);
	CLI_COMMAND argToCommand(char* arg);
	argcRange getArgCount(CLI_COMMAND command);
	void processCommand(CLI_COMMAND command, char* arg);
	void removeHashes(const std::vector<std::string>& fileList, const char* dataFolder);
};