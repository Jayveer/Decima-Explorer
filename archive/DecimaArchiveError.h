#pragma once
#include <string>
#include <iostream>

typedef enum DecimaArchiveError {
	OPENFAIL,
	WRITEFAIL,
	INVALIDMAGIC,
	DECOMPRESSFAIL,
	FINDINDEXFAIL,
	PARSEHEADERFAIL,
	INVALIDFILENAME,
	PARSEFILETABLEFAIL,
	PARSECHUNKTABLEFAIL
} DecimaArchiveError;

const std::string fileOpenError = "Failed to open input file";
const std::string fileWriteError = "Failed to open file for writing";
const std::string fileMagicError = "Input file is of an unrecognized format";
const std::string decompressError = "Failed to decompress data";
const std::string fileIndexError = "Failed to find index";
const std::string headerError = "Failed to parse header information";
const std::string fileTableError = "Failed to parse file table";
const std::string chunkTableError = "Failed to parse chunk table";
const std::string defaultError = "An unknown error occured";
const std::string filenameError = "Failed to find a file with that name";

void printError(std::string errorText) {
	std::cout << errorText << std::endl;
}

void showError(DecimaArchiveError error) {
	switch (error) {
	case OPENFAIL:
		printError(fileOpenError);
		break;
	case WRITEFAIL:
		printError(fileWriteError);
		break;
	case INVALIDMAGIC:
		printError(fileMagicError);
		break;
	case DECOMPRESSFAIL:
		printError(decompressError);
		break;
	case FINDINDEXFAIL:
		printError(fileIndexError);
		break;
	case INVALIDFILENAME:
		printError(filenameError);
		break;
	case PARSEHEADERFAIL:
		printError(headerError);
		break;
	case PARSEFILETABLEFAIL:
		printError(fileTableError);
		break;
	case PARSECHUNKTABLEFAIL:
		printError(chunkTableError);
		break;
	default:
		printError(defaultError);
		break;
	}
}