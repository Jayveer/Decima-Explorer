#pragma once
#include "../Component.h"

class ButtonCaller {
public:
	virtual void buttonPressed(HWND hwnd) = 0;
	virtual void buttonDrawing(HWND hwnd, HDC deviceContext) = 0;
};

class ButtonComponent : public Component {
private:
	ButtonCaller* caller = {};
	uint32_t backgroundColour;

public:
	
	ButtonComponent();
	~ButtonComponent();

	void clicked();
	void enable();
	void disable();
	void setCaller(ButtonCaller *caller);
	void setBackgroundColour(uint32_t colour);
	void setFont(int size, int weight, const char* fontface);
	void create(HWND parent, const char *name, Dimensions dimensions, Origin origin, DWORD extraStyle = 0);

	INT_PTR drawing(HDC deviceContext);
	uint32_t getBackgroundColour();
};
