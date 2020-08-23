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
		extract(arg);
		break;
	case REPACK:
		repack();
		break;
	case PACK:
		pack();
		break;
	case LIST:
		list();
		break;
	default:
		extract(arg);
	}
}

void CLI::run(const char* programName, const char* programVersion) {
	printf("Running %s v%s:\n", programName, programVersion);
	printf("Visit https://github.com/Jayveer/Decima-Explorer for updates:\n\n");
	if (!checkInput()) return;
	CLI_COMMAND command = argToCommand(argv[1]);

	processCommand(command, argv[3]);
}

void CLI::extract(char* arg) {
	isDirectory(argv[2]) ? directoryExtract(arg) : fileExtract(arg);
}

void CLI::archiveExtract(char* arg, DecimaArchive* archive) {
	archive->open();

	std::string output = setupOutput();

	if (isNumber(arg)) {
		int id = argToNumber(argv[3]);
		if (!archive->extractFile(id, output)) return;
	} else {
		if (!archive->extractFile(arg, output)) return;
	}

	printf("Finished extracting file %s\n", argv[4]);
}

void CLI::fileExtract(char* arg) {
	if (getFileExtension(argv[2]) == "mpk") {
		ArchiveMoviePack decimaArchive(argv[2]);
		archiveExtract(arg, &decimaArchive);
	} else {
		ArchiveBin decimaArchive(argv[2]);
		archiveExtract(arg, &decimaArchive);
	}
}

std::string CLI::setupOutput() {
	std::string output = argc == 5 ? argv[4] : argv[3];
	std::string path = getFilePathWithoutName(output);
	if (path != "") createDirectoriesFromPath(path);
	return output;
}

void CLI::directoryExtract(char* arg) {
	bool found = 0;
	std::vector<std::string> files = getFilesFromDirectory(argv[2], ".bin");

	if (isNumber(arg)) {
		printf("IDs cannot be used with directory extract");
		return;
	}

	std::string output = setupOutput();

	for (int i = 0; i < files.size(); i++) {
		ArchiveBin decimaArchive(files[i].c_str());
		if (!decimaArchive.open()) continue;
		found = decimaArchive.extractFile(arg, output, 1);
		if (found) break;
	}

	found ? printf("Finished extracting file %s\n", output.c_str()) : printf("Failed to find file %s\n", output.c_str());
}

void CLI::list() {
	BinInitial initial(argv[2]);
	if (!initial.open()) return;

	CorePrefetch prefetch;
	DataBuffer data = initial.extractFile(prefetch.getFilename());
	if (data.empty()) return;

	prefetch.open(data);
	std::unordered_map<uint64_t, const char*> hashMap;

	uint64_t numStrings = prefetch.getPrefetch()->numStrings;

	for (int i = 0; i < numStrings; i++) {
		uint64_t hash = getFileHash(prefetch.getPrefetch()->strings[i].string + ".core");
		hashMap[hash] = prefetch.getPrefetch()->strings[i].string.c_str();
	}

	ArchiveBin arc(argv[3]);
	arc.open();

	for (int i = 0; i < arc.getFileTable().size(); i++) {
		uint64_t hash = arc.getFileTable()[i].hash;

		if (hashMap[hash] != NULL) {
			const char* test = hashMap[hash];
			std::cout << i << ": " << test <<  "\n";
		}
	}
	int dummy = 0;

	//prefetch.extractFileTableStreamed(data);
	//printf("File list extracted successfully\n");
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
		return { 3, 4 };
	case REPACK:
		return { 4, 4 };
	case PACK:
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

void CLI::removeHashes(const std::vector<std::string>& fileList, const char *dataFolder) {
	std::vector<std::string> dataFiles = getFilesFromDirectory(dataFolder, ".bin");

	for (int i = 0; i < dataFiles.size(); i++) {
		ArchiveBin decimaArchive(dataFiles[i].c_str());
		if (!decimaArchive.open()) continue;
		decimaArchive.nukeHashes(fileList);
	}
}

void CLI::repack() {
	std::string baseDirectory = argv[3];
	std::vector<std::string> files;

	traverseDirectory(baseDirectory, "*", files);
	ArchiveBin decimaArchive(argv[2]);
	if (!decimaArchive.open()) return;
	decimaArchive.update(baseDirectory, files);
}

void CLI::pack() {
	std::string baseDirectory = argv[2];
	std::vector<std::string> files; 

	traverseDirectory(baseDirectory, "*", files);
	ArchiveBin decimaArchive(argv[3]);
	decimaArchive.create(baseDirectory, files);
}

void CLI::printUsage() {
	printf("%s", this->USAGE_MESSAGE);
}

void CLI::exit() {
	printf(this->EXIT_MESSAGE);
}