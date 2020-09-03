#pragma once
#include "component/textfield/TextFieldComponent.h"
#include "component/progress/ProgressComponent.h"
#include "component/window/WindowComponent.h"
#include "component/button/ButtonComponent.h"
#include "component/image/ImageComponent.h"
#include "component/view/ViewComponent.h"
#include "component/file/FileComponent.h"
#include "component/list/ListComponent.h"

class MainWindow : public ProcedureCaller {
private:
	WindowComponent window;
	LRESULT ProcedureWrapper(HWND inHwnd, UINT message, WPARAM wParam, LPARAM lParam);
public:
	MainWindow();
	~MainWindow();

	HWND getHandle();
	void create(HINSTANCE hInst, WindowCaller* caller, const char* title, HICON icon, HICON iconSm, uint32_t bgColour);
	void run(std::string programName, std::string version);
};