#pragma once
#include "../component.h"

class WindowCaller {
public:
	virtual void windowCreated(HWND hwnd) = 0;
	virtual void windowRightClicked(HWND hwnd, int mouseX, int mouseY) = 0;
};

class WindowComponent : public Component {
private:
	static LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	WindowCaller* caller = {};
	ProcedureCaller* pc = {};

public:
	
	WindowComponent(HINSTANCE hInst, const  char* name, const char* title, uint32_t colour, ProcedureCaller *pc);
	WindowComponent(ProcedureCaller* pc);
	~WindowComponent();

	int create(HINSTANCE hInst, const  char* name, const char* title, uint32_t colour);

	void run();
	void created();
	void setCaller(WindowCaller* caller);
	void rightClicked(int mouseX, int mouseY);
};