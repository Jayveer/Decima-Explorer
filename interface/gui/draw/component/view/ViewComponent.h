#pragma once
#include "../Component.h"

class ViewCaller {
public:
	virtual void viewClicked(HWND hwnd) = 0;
	virtual void viewDrawing(HWND hwnd, HDC deviceContext) = 0;
};


class ViewComponent : public Component {
private:
	ViewCaller* caller = {};
	uint32_t backgroundColour;
public:
	ViewComponent();
	~ViewComponent();

	void clicked();
	INT_PTR drawing(HDC deviceContext);
	uint32_t getBackgroundColour();
	void setCaller(ViewCaller* caller);
	void setBackgroundColour(uint32_t colour);
	void setFont(int size, int weight, const char* fontface);
	void create(HWND parent, Dimensions dimensions, Origin origin, DWORD extraStyle = 0);
};