#include "CLI.h"
#include "../file/prefetch/CorePrefetch.h"
#include "../archive/initial/ArchiveInitial.h"

CLI::CLI(int argc, char **argv) {
	this->argc = argc;
	this->argv = argv;
}

CLI::~CLI() {
}

void CLI::processCommand(CLI_COMMAND command, char* arg) {
	switch (command) {
	case EXTRACT:
		extract(arg);
		break;
	case REPACK:
		repack();
		break;
	case LIST:
		list();
		break;
	default:
		extract(arg);
	}
}

void CLI::run(const char* programName) {
	if (!checkInput()) return;
	printf("Running %s:\n", programName);

	CLI_COMMAND command = argToCommand(argv[1]);

	processCommand(command, argv[3]);
}

void CLI::extract(char* arg) {
	DecimaArchive decimaArchive(argv[2]);
	if (!decimaArchive.open()) return;

	if (isNumber(arg)) {
		int id = argToNumber(argv[3]);
		if (!decimaArchive.extractFile(id, argv[4])) return;
	} else {
		if (!decimaArchive.extractFile(argv[3], argv[4])) return;
	}

	printf("Finished extracting file %s\n", argv[4]);
}

void CLI::list() {
	ArchiveInitial initial(argv[2]);
	if (!initial.open()) return;

	CorePrefetch prefetch;
	DataBuffer data = initial.extractFile(prefetch.getFilename());
	if (data.empty()) return;

	prefetch.open(data);
	prefetch.extractFileTable();
	printf("File list extracted successfully\n");
}

bool CLI::checkInput() {
	if (!isCommand(argv[1])) {
		printUsage();
		return false;
	}

	int checkArgCount = getArgCount(argToCommand(argv[1]));

	if (argc != checkArgCount) {
		printUsage();
		return false;
	}

	return true;
}

int CLI::getArgCount(CLI_COMMAND command) {
	switch (command) {
	case EXTRACT:
		return 5;
	case LIST:
		return 3;
	case REPACK:
		return 5;
	default:
		return 5;
	}
}

int CLI::argToNumber(char* arg) {
	int num;
	sscanf(arg, "%d", &num);
	return num;
}

CLI_COMMAND CLI::argToCommand(char* arg) {
	if (!strcmp(arg, "-extract") || !strcmp(arg, "-e"))
		return EXTRACT;
	if (!strcmp(arg, "-list")    || !strcmp(arg, "-l"))
		return LIST;
	if (!strcmp(arg, "-repack")  || !strcmp(arg, "-r"))
		return REPACK;
}

bool CLI::isNumber(char* arg) {
	for (int i = 0; arg[i] != 0; i++) {
		if (!isdigit(arg[i]))
			return false;
	}
	return true;
}

bool CLI::isCommand(char* arg) {
	return arg[0] == 0x2D;
}

void CLI::repack() {
	printf("Sorry reapcking is not implemented yet\n");
}

void CLI::printUsage() {
	printf("%s", this->USAGE_MESSAGE);
}

void CLI::exit() {
	printf(this->EXIT_MESSAGE);
}