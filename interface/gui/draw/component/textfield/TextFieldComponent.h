#pragma once
#include "../Component.h"

class TextfieldCaller {
public:
	virtual void textfieldDrawing(HWND hwnd, HDC deviceContext) = 0;
};


class TextfieldComponent : public Component {
private:
	TextfieldCaller* caller = {};
	uint32_t backgroundColour;
public:
	TextfieldComponent();
	~TextfieldComponent();

	INT_PTR drawing(HDC deviceContext);
	uint32_t getBackgroundColour();
	void setCaller(TextfieldCaller* caller);
	void update();
	std::string getText();
	void setText(std::string text);
	void setBackgroundColour(uint32_t colour);
	void setFont(int size, int weight, const char* fontface);
	void create(HWND parent, Dimensions dimensions, Origin origin);

	std::string text;
};