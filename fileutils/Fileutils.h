#pragma once
#include <string>
#include <Windows.h>

inline
bool checkDirectoryExists(const std::string& dirName) {
    DWORD fileAttr = GetFileAttributesA(dirName.c_str());
    return (fileAttr & FILE_ATTRIBUTE_DIRECTORY);
}

inline
void createOutputDirectory(const std::string& dirName) {
	CreateDirectory(dirName.c_str(), NULL);
}

inline
void addExtension(std::string& dirName, std::string extension) {
    dirName += "." + extension;
}

inline
std::string getFileExtension(const std::string& dirName) {
    return dirName.substr(dirName.find_last_of(".") + 1);
}

inline
bool hasExtension(std::string dirName, std::string extension) {
    return getFileExtension(dirName) == extension;
}

inline 
void createDirectoriesFromPath(const std::string& path) {
    
}