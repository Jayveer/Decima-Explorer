#include "CLI.h"


CLI::CLI(int argc, char **argv) {
	this->argc = argc;
	this->argv = argv;
}

CLI::~CLI() {
}

void CLI::processCommand(CLI_COMMAND command, char* arg) {
	switch (command) {
	case EXTRACT:
		cliExtract();
		break;
	case REPACK:
		cliRepack();
		break;
	case PACK:
		cliPack();
		break;
	case LIST:
		list();
		break;
	case SWAP:
		cliSwap();
	default:
		cliExtract();
	}
}

void CLI::run(std::string programName, std::string version) {
	std::string startup = "Running " + programName + " v" + version + ":";
	std::string update = "Visit https://github.com/Jayveer/Decima-Explorer for updates:\n";
	showMessage(startup.c_str());
	showMessage(update.c_str());
	if (!checkInput()) return;

	CLI_COMMAND command = argToCommand(argv[1]);
	processCommand(command, argv[3]);
}

void CLI::cliExtract() {
	isDirectory(argv[2]) ? dirExtract() : fileExtract();
}

void CLI::fileExtract() {
	std::string output = argc == 5 ? argv[4] : argv[3];
	setupOutput(output);

	int done;
	if (isNumber(argv[3])) {
		int id = argToNumber(argv[3]);
		done = extract(argv[2], id, output.c_str());
	} else {
		done = extract(argv[2], argv[3], output.c_str());
	}

	if (done <= 0)
		showError("extraction failed (id/name not found)");
	else {
		std::string message = "finished extracting file " + output;
		showMessage(message.c_str());
	}
}

void CLI::dirExtract() {
	buildFileMap(argv[2]);

	if (isNumber(argv[3])) {
		showError("IDs cannot be used with directory extract");
		return;
	}

	if (checkFileExists(argv[3])) {
		std::string fileListName = argv[3];
		if (hasExtension(fileListName, "txt")) {
			int done = fileListExtract(fileListName.c_str());

			char buf[512] = {0};
			snprintf(buf, sizeof(buf), "finished extracting %s list, total: %d", fileListName.c_str(), done);
			std::string message = buf;

			showMessage(message.c_str());
			return;
		}
	}

	std::string output = argc == 5 ? argv[4] : argv[3];
	int done = directoryExtract(argv[3], output);
	if (done <= 0)
		showError("extraction failed (name not found)");
	else {
		std::string message = "finished extracting file " + output;
		showMessage(message.c_str());
	}
}

void CLI::list() {
	initPrefetch(argv[2]);
	prefetchFile.extractFileTable();
	showMessage("File table extracted to file_list.txt");

	extractFileMap(argv[2]);
	showMessage("Hash table extracted to file_hash.txt");
}

bool CLI::checkInput() {
	if (argc < 2) {
		printUsage();
		return false;
	}

	if (!isCommand(argv[1])) {
		printUsage();
		return false;
	}

	argcRange range = getArgCount(argToCommand(argv[1]));

	if (argc < range.low || argc > range.high) {
		printUsage();
		return false;
	}

	return true;
}

argcRange CLI::getArgCount(CLI_COMMAND command) {
	switch (command) {
	case EXTRACT:
		return { 4, 5 };
	case LIST:
		return { 3, 3 };
	case REPACK:
		return { 4, 4 };
	case PACK:
		return { 4, 4 };
	case SWAP:
		return { 4, 4 };
	default:
		return { 5, 5 };
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
	if (!strcmp(arg, "-pack") || !strcmp(arg, "-p"))
		return PACK;
	if (!strcmp(arg, "-swap") || !strcmp(arg, "-s"))
		return SWAP;
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

void CLI::cliRepack() {
	std::vector<std::string> files = getFiles(argv[3]);
	repack(files, argv[2], argv[3]);
}

void CLI::cliPack() {
	std::vector<std::string> files = getFiles(argv[2]);
	pack(files, argv[2], argv[3]);
}

void CLI::cliSwap() {
	swap(argv[2], argv[3]);
}

void CLI::printUsage() {
	showMessage(this->USAGE_MESSAGE);
}

void CLI::exit() {
	printf(this->EXIT_MESSAGE);
}

void CLI::update() {};
void CLI::intervalUpdate() {};

void CLI::showError(const char* message) {
	std::cout << "Error: " << message << std::endl;
}

void CLI::showWarning(const char* message) {
	std::cout << "Warning: " << message << std::endl;
}

void CLI::showMessage(const char* message) {
	std::cout << message << std::endl;
}