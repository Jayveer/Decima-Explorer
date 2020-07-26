#pragma once
#include <io.h> 
#include <string>
#include <vector>
#include <iostream>
#include <Windows.h>


inline
std::vector<std::string> getFilesFromDirectory(const std::string& dirName, const std::string& extension) {
    WIN32_FIND_DATA file_data;
    std::vector<std::string> fileList;
    std::string filepath = dirName + "\\*" + extension;

    HANDLE dir = FindFirstFile(filepath.c_str(), &file_data);
    if (dir == INVALID_HANDLE_VALUE) return fileList;

    do {
        std::string file_name = file_data.cFileName;
        std::string full_file_name = dirName + "\\" + file_name;
        bool isDirectory = (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;

        if (isDirectory) continue;
        if (file_name[0] == '.') continue;
        fileList.push_back(full_file_name);

    } while (FindNextFile(dir, &file_data));

    FindClose(dir);
    return fileList;
}

inline
bool hasPathSeparator(const std::string& path) {
    if (path.size() < 2) return false;
    std::string output = path.substr(path.size() - 1);
    bool val = output == "\\";
    return output == "\\";
}

inline
bool isDirectory(const std::string& dirName) {
    DWORD fileAttr = GetFileAttributesA(dirName.c_str());
    return (fileAttr & FILE_ATTRIBUTE_DIRECTORY);
}

inline
bool checkFileExists(const std::string& filename) {
    return _access(filename.c_str(), 0) == 0;
}

inline
std::string addFileToPath(const std::string& filename, const std::string& path) {
    return hasPathSeparator(path) ? path + filename : path + "\\" + filename;
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


struct membuf : std::streambuf
{
    membuf(char* base, std::ptrdiff_t n) {
        this->setg(base, base, base + n);
    }

    virtual pos_type seekoff(off_type off, std::ios_base::seekdir dir, std::ios_base::openmode which = std::ios_base::in) {
        if (dir == std::ios_base::cur) gbump(off);
        return gptr() - eback();
    }
};