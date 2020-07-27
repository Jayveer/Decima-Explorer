#pragma once

typedef enum ArchiveBinError {
	INVALIDMAGIC,
	DECOMPRESSFAIL,
	PARSEFILETABLEFAIL,
	PARSECHUNKTABLEFAIL
} ArchiveBinError;

const std::string fileMagicError	= "Input file is of an unrecognized format";
const std::string decompressError	= "Failed to decompress data";
const std::string fileTableError	= "Failed to parse file table";
const std::string chunkTableError	= "Failed to parse chunk table";

inline
void showError(ArchiveBinError error) {
	switch (error) {
	case INVALIDMAGIC:
		printError(fileMagicError);
		break;
	case DECOMPRESSFAIL:
		printError(decompressError);
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