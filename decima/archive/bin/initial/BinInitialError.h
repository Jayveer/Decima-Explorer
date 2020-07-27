#pragma once

typedef enum ArchiveInitialError {
	NOTFOUND,
} ArchiveInitialError;

const std::string notFoundError = "Failed to find initial archive";

inline
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
