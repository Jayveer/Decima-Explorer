#pragma once
#include "draw/MainWindow.h"

#include <thread>
#include "../decima/file/prefetch/CorePrefetch.h"
#include "../decima/archive/mpk/ArchiveMoviePack.h"
#include "../decima/archive/bin/initial/BinInitial.h"
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

	const char* aboutText = "Decima Explorer is a free and open source program. If you paid for this program demand your money back from the seller.\n\n Created by Jayveer\n https://github.com/Jayveer/Decima-Explorer \n\nSpecial Thanks for work on decryption.\n Ekey https://github.com/Ekey \n Wunkolo https://github.com/wunkolo \n\nLibraries:\n Ooz By Powzix https://github.com/powzix/ooz \n Murmur3 by Peter Scott https://github.com/PeterScott/murmur3 \n MD5 by Aladdin Enterprises";

	void initExtractButton(HWND parent);
	void initBrowseButton(HWND parent);
	void initBrowserView(HWND parent);
	void initFooterView(HWND parent);
	void initFileList(HWND parent);
	void initTextbox(HWND parent);

	void addFilesToRows();
	void directoryChosen(std::string directory);
	void saveDirectoryChosen(std::string directory);
	void directoryExtract(std::string filename, std::string output, std::string fileDirectory);

	void viewDrawing(HWND hwnd);
	void listSelected(HWND hwnd);
	void listScrolled(HWND hwnd);
	void windowCreated(HWND hwnd);
	void buttonPressed(HWND hwnd);
	void buttonDrawing(HWND hwnd);
	void windowRightClicked(HWND hwnd, int mouseX, int mouseY);
	
	void listRightClicked(HWND hwnd, int mouseX, int mouseY);
	void textfieldDrawing(HWND hwnd, HDC deviceContext);

	bool reachedEnd();
	void resetData();
	DataBuffer prefetchData;
	membuf *sbuf;
	std::istream *prefetchStream;
public:
	GUI(HINSTANCE hInst);
	~GUI();
	
	void run(std::string programName, std::string version);
};