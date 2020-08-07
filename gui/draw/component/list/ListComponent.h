#pragma once
#include "../Component.h"

class ListCaller {
public:
	virtual void listRightClicked(HWND hwnd, int mouseX, int mouseY) = 0;
	virtual void listSelected(HWND hwnd) = 0;
	virtual void listScrolled(HWND hwnd) = 0;
};


class ListComponent : public Component {
private:
	ListCaller* caller = {};
	uint32_t backgroundColour;
public:
	ListComponent();
	~ListComponent();

	void selected();
	INT_PTR drawing(HDC deviceContext);
	uint32_t getBackgroundColour();
	int getNumSelected();
	void setCaller(ListCaller* caller);
	void setBackgroundColour(uint32_t colour);
	void rightClicked(int mouseX, int mouseY);
	void setFont(int size, int weight, const char* fontface);
	void create(HWND parent, Dimensions dimensions, Origin origin);
	int createItem(int index, const char * text);
	void scrolled();
	int createSubItem(int index, int column, const char* text);
	int createColumn(int column, std::string Text, int width);
};