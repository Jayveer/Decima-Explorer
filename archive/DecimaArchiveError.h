#pragma once
#include <string>
#include <iostream>

typedef enum DecimaArchiveError {
	OPENFAIL,
	WRITEFAIL,
	PARSEHEADERFAIL,
	INVALIDFILENAME,
} DecimaArchiveError;


const std::string defaultError		= "An unknown error occured";
const std::string headerError		= "Failed to parse header information";
const std::string fileOpenError		= "Failed to open input file";
const std::string fileWriteError	= "Failed to open file for writing";
const std::string filenameError		= "Failed to find a file with that name";

inline
void printError(std::string errorText) {
	std::cout << errorText << std::endl;
}

inline
void showError(DecimaArchiveError error) {
	switch (error) {
	case OPENFAIL:
		printError(fileOpenError);
		break;
	case WRITEFAIL:
		printError(fileWriteError);
		break;
	case INVALIDFILENAME:
		printError(filenameError);
		break;
	case PARSEHEADERFAIL:
		printError(headerError);
		break;
	default:
		printError(defaultError);
		break;
	}
}