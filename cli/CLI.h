#pragma once

typedef enum CLI_COMMAND {
	LIST,
	EXTRACT,
	REPACK
} CLI_COMMAND;

class CLI {
public:
	CLI(int argc, char **argv);
	~CLI();

	void run(const char* programName);
	void exit();
private:

	int argc;
	char **argv;

	const char *USAGE_MESSAGE = "Usage:\t DecimaExplorer.exe [-e/-extract] inputfile fileid outputfile \n\t DecimaExplorer.exe [-e/-extract] inputfile filename outputfile\n\t DecimaExplorer.exe [-l/-list] [directory containing initial binary]\nAvailable Options:\n\tList:    -l, -list\n\tExtract: -e, -extract\n";
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
	int argToNumber(char* arg);
	void fileExtract(char* arg);
	void directoryExtract(char* arg);
	CLI_COMMAND argToCommand(char* arg);
	int getArgCount(CLI_COMMAND command);
	void processCommand(CLI_COMMAND command, char* arg);
};