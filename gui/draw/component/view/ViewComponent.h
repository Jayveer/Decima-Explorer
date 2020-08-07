#pragma once
#include "../Component.h"

class ViewCaller {
public:
	virtual void viewDrawing(HWND hwnd) = 0;
};


class ViewComponent : public Component {
private:
	ViewCaller* caller = {};
	uint32_t backgroundColour;
public:
	ViewComponent();
	~ViewComponent();

	INT_PTR drawing();
	uint32_t getBackgroundColour();
	void setCaller(ViewCaller* caller);
	void setBackgroundColour(uint32_t colour);
	void create(HWND parent, Dimensions dimensions, Origin origin);
};