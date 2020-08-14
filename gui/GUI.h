#pragma once
#include "draw/MainWindow.h"

#include <thread>
#include <future>
#include <unordered_map>

#include "../decima/file/prefetch/CorePrefetch.h"
#include "../decima/archive/mpk/ArchiveMoviePack.h"
#include "../decima/archive/bin/initial/BinInitial.h"
#include "../utils/Arrayutils.h"
#include "../utils/NumUtils.h"

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

class GUI : public ButtonCaller, WindowCaller, ViewCaller, TextfieldCaller, ListCaller {
private:
	MainWindow mainWindow;
	ButtonComponent browseButton;
	ViewComponent browserView;
	ImageComponent header;
	TextfieldComponent textbox;
	ListComponent fileList;
	ButtonComponent extractButton;
	ViewComponent footerView;
	ProgressComponent extractProgress;

	int32_t progressNum;
	std::mutex* progressMutex;

	bool forceQuit = false;


	const char* aboutText = "Decima Explorer is a free and open source program. If you paid for this program demand your money back from the seller.\n\n Created by Jayveer\n https://github.com/Jayveer/Decima-Explorer \n\nSpecial Thanks for work on decryption.\n Ekey https://github.com/Ekey \n Wunkolo https://github.com/wunkolo \n\nLibraries:\n Ooz By Powzix https://github.com/powzix/ooz \n Murmur3 by Peter Scott https://github.com/PeterScott/murmur3 \n MD5 by Aladdin Enterprises";

	void resetData();
	void enableElements();
	void disableElements();

	void initTextbox(HWND parent);
	void initFileList(HWND parent);
	void initFooterView(HWND parent);
	void initBrowserView(HWND parent);
	void initBrowseButton(HWND parent);
	void initExtractButton(HWND parent);
	void initExtractProgress(HWND parent);

	void deinitFileList();
	void deinitExtractProgress();

	void checkQueue();
	void addFilesToRows();
	int32_t getProgress();
	void updateProgress(int count);
	std::vector<char*> getSelectedStrings();
	void directoryChosen(std::string directory);
	void saveDirectoryChosen(std::string directory);
	std::vector<char*> buildFileMap(const char* fileDirectory);
	void directoryExtract(const char* filename, std::string output);
	void parallelExtract(const std::string& directory, const std::vector<char*>& selectedStrings);
	HICON fetchIcon(const unsigned char* buffer, int bufferSize, int iconSize, int width, int height);
	void batchExtract(const std::vector<char*>& filenames, std::string output, int batchSize, int batchOffset);

	void viewDrawing(HWND hwnd);
	void listSelected(HWND hwnd);
	void listScrolled(HWND hwnd);
	void windowCreated(HWND hwnd);
	void buttonPressed(HWND hwnd);
	void buttonDrawing(HWND hwnd);
	void textfieldDrawing(HWND hwnd, HDC deviceContext);
	void listRightClicked(HWND hwnd, int mouseX, int mouseY);
	void windowRightClicked(HWND hwnd, int mouseX, int mouseY);

	DataBuffer prefetchData;
	membuf *sbuf;
	std::istream *prefetchStream;
	std::vector<std::future<void>> pending_futures;
	std::unordered_map<uint64_t, const char*> fileMap;
public:
	GUI(HINSTANCE hInst);
	~GUI();

	
	void run(std::string programName, std::string version);
};