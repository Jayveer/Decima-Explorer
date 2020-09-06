#include "FileComponent.h"
#include <iostream>
FileComponent::FileComponent() {
}

FileComponent::~FileComponent() {
}

void FileComponent::setCaller(FileCaller* caller) {
}

//	std::vector<FileFilter> filter;
//filter.push_back({ L"Word Document (*.doc)", L"*.doc" });

void FileComponent::create(HWND parent, DWORD options, const std::vector<FileFilter>& filter) {
	bool ok = 0;
	char str[MAX_PATH];
	IFileOpenDialog* pFileOpen;
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);	
	hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));

	if (!filter.empty())
		pFileOpen->SetFileTypes(filter.size(), (COMDLG_FILTERSPEC*)&filter[0]);

	if (SUCCEEDED(hr)) {

		if (SUCCEEDED(hr)) {
			pFileOpen->SetOptions(options);

			hr = pFileOpen->Show(NULL);

			if (SUCCEEDED(hr)) {
				IShellItem* pItem;
				hr = pFileOpen->GetResult(&pItem);

				if (SUCCEEDED(hr)) {
					PWSTR pszFilePath;
					hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

					std::wstring test = pszFilePath;

					filename = wcstombs(str, pszFilePath, MAX_PATH);
					ok = 1;
				}
				pItem->Release();
			}
			pFileOpen->Release();
		}
		CoUninitialize();
	}

	this->filename = ok ? str : "";
}


std::string FileComponent::getFilename() {
	return this->filename;
}




//FILE
/*char filename[MAX_PATH];
OPENFILENAME ofn = {0};

ofn.lStructSize = sizeof(ofn);
ofn.hwndOwner = parent;
ofn.lpstrFile = filename;
ofn.lpstrFile[0] = '\0';
ofn.nMaxFile = MAX_PATH;
ofn.lpstrFilter = "Folder\0\n\0All Supported Files(*.bin;*.mpk)\0*.bin;*.mpk\0Decima Binary(*.bin)\0*.bin\0Decima Movie Pack(*.mpk)\0*.mpk\0";
ofn.nFilterIndex = 1;
//ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
//ofn.lpstrDefExt = "core";

ofn.Flags = !OFN_FILEMUSTEXIST;

GetOpenFileName(&ofn);
this->filename = filename;*/

//FOLDER
/*char filename[MAX_PATH];
const char* path_param = this->filename.c_str();

BROWSEINFO bi = { 0 };
bi.lpszTitle = ("Browse for folder...");
bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
bi.lParam = (LPARAM)path_param;

LPITEMIDLIST pidl = SHBrowseForFolder(&bi);

if (pidl != 0)
{
	//get the name of the folder and put it in path
	SHGetPathFromIDList(pidl, filename);

	//free memory used
	IMalloc* imalloc = 0;
	if (SUCCEEDED(SHGetMalloc(&imalloc)))
	{
		imalloc->Free(pidl);
		imalloc->Release();
	}

	this->filename = filename;
}*/
