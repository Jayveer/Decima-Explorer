#pragma once

extern void printError(std::string errorText);
const std::string defaultError;

typedef enum ArchiveInitialError {
	NOTFOUND,
} ArchiveInitialError;

const std::string notFoundError = "Failed to find initial archive";

void showError(ArchiveInitialError error) {
	switch (error) {
	case NOTFOUND:
		printError(notFoundError);
		break;
	default:
		printError(defaultError);
		break;
	}
}