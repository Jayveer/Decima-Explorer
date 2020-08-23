#pragma once
#include "../Component.h"

class ButtonCaller {
public:
	virtual void buttonPressed(HWND hwnd) = 0;
	virtual void buttonDrawing(HWND hwnd) = 0;
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
	void create(HWND parent, const char *name, Dimensions dimensions, Origin origin);

	INT_PTR drawing();
	uint32_t getBackgroundColour();
};
