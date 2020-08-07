#include "WindowComponent.h"
#include "../../../../resource.h"

WindowComponent::WindowComponent(ProcedureCaller* pc) {
	setType(WINDOW);
	this->pc = pc;
}

WindowComponent::WindowComponent(HINSTANCE hInst, const char* name, const char* title, uint32_t colour, ProcedureCaller *pc) {
	this->pc = pc;
	create(hInst, name, title, colour);
}

WindowComponent::~WindowComponent() {
}

void WindowComponent::created() {
	caller->windowCreated(getHandle());
}

void WindowComponent::setCaller(WindowCaller* caller) {
	this->caller = caller;
}

void WindowComponent::rightClicked(int mouseX, int mouseY) {
	this->caller->windowRightClicked(getHandle(), mouseX, mouseY);
}

int WindowComponent::create(HINSTANCE hInst, const char* name, const char* title, uint32_t colour) {
	HBRUSH bgColour = createBrush(colour);

	WNDCLASS windowClass = {};
	windowClass.hInstance = hInst;
	windowClass.lpszClassName = name;
	windowClass.lpfnWndProc = &WindowProcedure;
	windowClass.hbrBackground = bgColour;
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1));

	if (!RegisterClass(&windowClass)) return 0;

	DWORD style = WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX | WS_VISIBLE;
	HWND hwnd = CreateWindow(name, title, style, CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720, NULL, NULL, hInst, this);
	setHandle(hwnd);
	return 1;
}

void WindowComponent::run() {
	MSG msg = {};

	while (GetMessage(&msg, NULL, NULL, NULL)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

LRESULT CALLBACK WindowComponent::WindowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	WindowComponent* wc;

	if (msg == WM_CREATE) {
		CREATESTRUCT* cs = (CREATESTRUCT*)lParam;
		wc = (WindowComponent*)cs->lpCreateParams;
		wc->setHandle(hwnd);

		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)wc);
		return wc ? wc->pc->ProcedureWrapper(hwnd, msg, wParam, lParam) : DefWindowProc(hwnd, msg, wParam, lParam);
	}

	wc = (WindowComponent*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
	return wc ? wc->pc->ProcedureWrapper(hwnd, msg, wParam, lParam) : DefWindowProc(hwnd, msg, wParam, lParam);
}