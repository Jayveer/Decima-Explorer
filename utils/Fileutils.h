#pragma once
#include <io.h> 
#include <string>
#include <vector>
#include <iostream>
#include <Windows.h>
#include <stack>

inline
bool traverseDirectory(std::string basePath, const std::string& mask, std::vector<std::string>& files) {
    HANDLE hFind = INVALID_HANDLE_VALUE;
    WIN32_FIND_DATA ffd;
    std::string spec;
    std::string path;
    std::stack<std::string> directories;

    directories.push("");
    files.clear();

    basePath += "\\";
    while (!directories.empty()) {
        path = directories.top();
        spec = basePath + path + mask;
        directories.pop();

        hFind = FindFirstFile(spec.c_str(), &ffd);
        if (hFind == INVALID_HANDLE_VALUE) {
            return false;
        }

        do {
            if (strcmp(ffd.cFileName, ".") != 0 &&
                strcmp(ffd.cFileName, "..") != 0) {
                if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                    directories.push(path + ffd.cFileName + "/");
                }
                else {
                    files.push_back(path + ffd.cFileName);
                   // filesizes.push_back(ffd.nFileSizeHigh);
                }
            }
        } while (FindNextFile(hFind, &ffd) != 0);

        if (GetLastError() != ERROR_NO_MORE_FILES) {
            FindClose(hFind);
            return false;
        }

        FindClose(hFind);
        hFind = INVALID_HANDLE_VALUE;
    }

    return true;
}

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
bool checkDirectoryExists(const std::string& dirName) {
    DWORD fileAttr = GetFileAttributesA(dirName.c_str());
    return fileAttr != INVALID_FILE_ATTRIBUTES;
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
bool createOutputDirectory(const std::string& dirName) {
	return CreateDirectory(dirName.c_str(), NULL);
}

inline
void addExtension(std::string& dirName, const std::string& extension) {
    dirName += "." + extension;
}

inline
std::string getFileExtension(const std::string& dirName) {
    return dirName.substr(dirName.find_last_of(".") + 1);
}

inline
bool hasExtension(const std::string& dirName, const std::string& extension) {
    return getFileExtension(dirName) == extension;
}

inline
bool hasExtension(const std::string& dirName) {
    return getFileExtension(dirName) != dirName;
}

inline
std::string getFilePathWithoutName(const std::string& filename) {
    int slashIndex = filename.find_last_of("\\/");
    return slashIndex != std::string::npos ? filename.substr(0, slashIndex) : "";
}

inline
void createDirectoriesFromPath(const std::string& path) {
    if (!checkDirectoryExists(path)) {
        std::size_t slashIndex = path.find_last_of("\\/");
        if (slashIndex != std::string::npos) {
            createDirectoriesFromPath(path.substr(0, slashIndex));
        }
        createOutputDirectory(path);
    }
}

inline
uint32_t getFilesize(FILE* f) {
    fseek(f, 0, SEEK_END);
    uint32_t filesize = ftell(f);
    fseek(f, 0, SEEK_SET);

    return filesize;
}

inline
void shiftData(const std::string& filename, uint64_t insertionPoint, uint64_t insertionNum) {
    FILE* f;
    fopen_s(&f, filename.c_str(), "r+b");

    fseek(f, 0, SEEK_END);
    uint64_t fileSize = _ftelli64(f);

    uint64_t dataSize = fileSize - insertionPoint;

    uint64_t partitionSize = 51200000;
    uint64_t numPartitions = dataSize / partitionSize;
    uint64_t remainder = dataSize % partitionSize;
    if (remainder) numPartitions++;

    uint64_t pos = fileSize;

    for (int i = 0; i < numPartitions; i++) {
        bool firstPartition = i == 0;
        uint64_t size = partitionSize;

        if (firstPartition && remainder) size = remainder;
        pos -= size;

        std::vector<uint8_t> buffer(size);
        _fseeki64(f, pos, SEEK_SET);
        fread(&buffer[0], size, 1, f);
        _fseeki64(f, pos + insertionNum, SEEK_SET);
        fwrite(&buffer[0], size, 1, f);
    }

    fclose(f);
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