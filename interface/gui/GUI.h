#pragma once
#include "../Interface.h"
#include "draw/MainWindow.h"

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

struct FileInfo {
	const char* file;
	uint32_t size;
};

class GUI : public Interface, ButtonCaller, WindowCaller, ViewCaller, TextfieldCaller, ListCaller, ExtListCaller {
private:
	MainWindow mainWindow;

	ImageComponent header;

	ListComponent fileList;

	ViewComponent footerView;
	ViewComponent browserView;
	ViewComponent closeFilterButton;

	ButtonComponent browseButton;
	ButtonComponent extractButton;

	TextfieldComponent filterTextbox;
	TextfieldComponent browseTextbox;

	ProgressComponent extractProgress;

#ifdef PACKER
	bool isPacker = true;
#else
	bool isPacker = false;
#endif

	int32_t progressNum;
	bool redrawList = true;
	std::vector<FileInfo> fileInfo;
	std::vector<std::string> files;

	const char* aboutText = "Decima Explorer is a free and open source program. If you paid for this program demand your money back from the seller.\n\n Created by Jayveer\n https://github.com/Jayveer/Decima-Explorer \n\nSpecial Thanks for work on decryption.\n Ekey https://github.com/Ekey \n Wunkolo https://github.com/wunkolo \n\nLibraries:\n Ooz By Powzix https://github.com/powzix/ooz \n Murmur3 by Peter Scott https://github.com/PeterScott/murmur3 \n MD5 by Aladdin Enterprises";

#if PACKER
	std::vector<std::string> getSelectedStrings();
#else
	std::vector<char*> getSelectedStrings();
#endif

	void resetData();
	void openFilter();
	void closeFilter();
	void enableElements();
	void disableElements();

	void initFilter(HWND parent);
	void initTextbox(HWND parent);
	void initFileList(HWND parent);
	void initFooterView(HWND parent);
	void initBrowserView(HWND parent);
	void initBrowseButton(HWND parent);
	void initExtractButton(HWND parent);
	void initCloseFilterButton(HWND parent);
	void initExtractProgress(HWND parent, int32_t size);

	void deinitFilter();
	void deinitFileList();
	void deinitExtractButton();
	void deinitExtractProgress();
	void deinitCloseFilterButton();

	void showError(const char* message);
	void showMessage(const char* message);
	void showWarning(const char* message);

	void checkQueue();
	void addFilesToRows();
	void filterList(const std::string& filter);
	void directoryChosen(std::string directory);
	void saveDirectoryChosen(std::string directory);
	void populateFileInfo(const std::string& filter = "");
	void addFileInfo(const char* name, uint32_t size);
	HICON fetchIcon(const unsigned char* buffer, int bufferSize, int iconSize, int width, int height);

	void listFilter(HWND hwnd);
	void viewClicked(HWND hwnd);
	void listSelected(HWND hwnd);
	void listScrolled(HWND hwnd);
	void windowCreated(HWND hwnd);
	void buttonPressed(HWND hwnd);
	void textfieldChanged(HWND hwnd);
	void columnClicked(HWND hwnd, int col);
	void listAddItem(HWND hwnd, LV_ITEM* item);
	void columnSortAscending(HWND hwnd, int col);
	void columnSortDescending(HWND hwnd, int col);
	void viewDrawing(HWND hwnd, HDC deviceContext);
	void buttonDrawing(HWND hwnd, HDC deviceContext);
	void textfieldDrawing(HWND hwnd, HDC deviceContext);
	void listRightClicked(HWND hwnd, int mouseX, int mouseY);
	void windowRightClicked(HWND hwnd, int mouseX, int mouseY);

	void exit();
	void update();
	void intervalUpdate();
public:
	GUI(HINSTANCE hInst);
	~GUI();

	
	void run(std::string programName, std::string version);
};