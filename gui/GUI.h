#pragma once
#include <string>
#include <Windows.h>

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

class GUI {
private:
	WNDCLASS windowClass = { 0 };
	HWND hwnd = { 0 };
	MSG msg = { 0 };

	static LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	void createBrowseButton();
	int createWindow(HINSTANCE hInst);
public:
	GUI(HINSTANCE hInst);
	~GUI();

	void run(std::string programName, std::string programVersion);
};