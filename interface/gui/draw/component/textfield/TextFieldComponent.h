#pragma once
#include "../Component.h"

class TextfieldCaller {
public:
	virtual void textfieldChanged(HWND hwnd) = 0;
	virtual void textfieldDrawing(HWND hwnd, HDC deviceContext) = 0;
};


class TextfieldComponent : public Component {
private:
	TextfieldCaller* caller = {};
	uint32_t backgroundColour;
public:
	TextfieldComponent();
	~TextfieldComponent();

	void update();
	void changed();
	std::string getText();
	void setText(std::string text);
	uint32_t getBackgroundColour();
	INT_PTR drawing(HDC deviceContext);
	void setCaller(TextfieldCaller* caller);
	void setTextBackGroundColour();
	void setPlacheolderText(std::wstring text);
	void setBackgroundColour(uint32_t colour);
	void setFont(int size, int weight, const char* fontface);
	void create(HWND parent, Dimensions dimensions, Origin origin, DWORD extraStyle = 0);

	std::string text;
};