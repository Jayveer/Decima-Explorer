#include "GUI.h"

GUI::GUI(HINSTANCE hInst) {
	createWindow(hInst);
}

GUI::~GUI() {

}

int GUI::createWindow(HINSTANCE hInst) {
	windowClass = { 0 };
	//HBRUSH bgColour = CreateSolidBrush(RGB("0", "0", "0"));
	windowClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.hInstance = hInst;
	windowClass.lpszClassName = "GUI";
	windowClass.lpfnWndProc = WindowProcedure;

	if (!RegisterClass(&windowClass)) return 0;
	DWORD style = WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX | WS_VISIBLE;
	hwnd = CreateWindow("GUI", NULL, style, CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720, NULL, NULL, hInst, NULL);
	return 1;
}

void GUI::createBrowseButton() {
	RECT rect;
	GetWindowRect(hwnd, &rect);
	DWORD style = WS_VISIBLE | WS_CHILD;
	CreateWindow("Button", "Browse", style, 0, 0, 98, 20, hwnd, NULL, NULL, NULL);
}

void GUI::run(std::string programName, std::string programVersion) {
	SetWindowText(hwnd, programName.c_str());
	
	while (GetMessage(&msg, NULL, NULL, NULL)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}




/* static methods */


void cbb(HWND hwnd) {
	RECT rect;
	GetWindowRect(hwnd, &rect);
	DWORD style = WS_VISIBLE | WS_CHILD;
	CreateWindow("Button", "Browse", style, 1150, 10, 98, 20, hwnd, NULL, NULL, NULL);
}



HBITMAP loadImage(std::string filename) {
	HBITMAP image = (HBITMAP)LoadImage(NULL, filename.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	return image;
}

void addHeader(HWND hwnd, HBITMAP image) {
	DWORD style = WS_VISIBLE | WS_CHILD | SS_BITMAP;
	HWND header = CreateWindow("static", NULL, style, 0, 0, 1280, 177, hwnd, NULL, NULL, NULL);
	SendMessage(header, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)image);
}

HWND createBrowserView(HWND hwnd) {
	DWORD style = WS_VISIBLE | WS_CHILD;
	HWND browserView = CreateWindow("static", "test", style, 0, 177, 1280, 40, hwnd, NULL, NULL, NULL);
	return browserView;
}

HWND addBrowserView(HWND hwnd) {
	HWND bv = createBrowserView(hwnd);
	cbb(bv);
	return bv;
}

LRESULT CALLBACK GUI::WindowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_CREATE:
		addHeader(hwnd, loadImage("dexbg_s_3.bmp"));
		addBrowserView(hwnd);
		break;
	case WM_CTLCOLORSTATIC:
		return (INT_PTR)CreateSolidBrush(RGB(255, 0, 0));
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}