#pragma once
#include "../Component.h"

class ImageCaller {
public:
	virtual void viewDrawing(HWND hwnd) = 0;
	virtual void viewRightClicked(HWND hwnd, int mouseX, int mouseY) = 0;
};


class ImageComponent : public Component {
private:
	ImageCaller* caller = {};
	uint32_t backgroundColour;
	HBITMAP loadImage(const char* string);
public:
	ImageComponent();
	~ImageComponent();

	INT_PTR drawing();
	uint32_t getBackgroundColour();
	void setCaller(ImageCaller* caller);
	void rightClicked(int mouseX, int mouseY);
	void setBackgroundColour(uint32_t colour);
	void create(HWND parent, Dimensions dimensions, Origin origin, const char *imageFile);
};