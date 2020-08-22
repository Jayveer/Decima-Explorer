#pragma once

typedef enum ArchiveBinError {
	INVALIDMAGIC,
	COMPRESSFAIL,
	DECOMPRESSFAIL,
	PARSEFILETABLEFAIL,
	PARSECHUNKTABLEFAIL
} ArchiveBinError;

const std::string fileMagicError	= "Input file is of an unrecognized format";
const std::string compressError		= "Failed to compress data, please make sure you have oo2core_7_win64.dll in the same directory as Decima Explorer";
const std::string decompressError	= "Failed to decompress data";
const std::string fileTableError	= "Failed to parse file table";
const std::string chunkTableError	= "Failed to parse chunk table";

inline
void showError(ArchiveBinError error) {
	switch (error) {
	case INVALIDMAGIC:
		printError(fileMagicError);
		break;
	case COMPRESSFAIL:
		printError(compressError);
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