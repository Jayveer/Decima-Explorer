#pragma once
#include "../Component.h"
#include <shlobj_core.h>
#include <shobjidl_core.h>
struct FileFilter {
	const char* name;
	const char* ext;
};

class FileCaller {
public:
	virtual void FileDrawing(HWND hwnd) = 0;
};

class FileComponent : public Component {
private:
	std::string filename;
	FileCaller* caller = {};
public:
	FileComponent();
	~FileComponent();
	std::string getFilename();
	void setCaller(FileCaller* caller);
	void create(HWND parent);
};