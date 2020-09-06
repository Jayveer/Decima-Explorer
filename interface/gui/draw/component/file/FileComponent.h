#pragma once
#include "../Component.h"
#include <shlobj_core.h>
#include <shobjidl_core.h>
struct FileFilter {
	const wchar_t* name;
	const wchar_t* ext;
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
	DWORD defaultOptions = 0x1808;
	FileComponent();
	~FileComponent();
	std::string getFilename();
	void setCaller(FileCaller* caller);
	void create(HWND parent, DWORD options = 0x1808, const std::vector<FileFilter>& filter = {});
};