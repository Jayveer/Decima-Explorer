#pragma once
#include "../Component.h"

class ExtListCaller {
public:
	virtual void listFilter(HWND hwnd) = 0;
	virtual void listAddItem(HWND hwnd, LV_ITEM* item) = 0;
	virtual void columnSortAscending(HWND hwnd, int col) = 0;
	virtual void columnSortDescending(HWND hwnd, int col) = 0;
};

class ListCaller {
public:
	virtual void listSelected(HWND hwnd) = 0;
	virtual void listScrolled(HWND hwnd) = 0;
	virtual void columnClicked(HWND hwnd, int col) = 0;
	virtual void listRightClicked(HWND hwnd, int mouseX, int mouseY) = 0;
};


class ListComponent : public Component {
private:
	ListCaller* caller = {};
	ExtListCaller* extCaller = {};
	uint32_t backgroundColour;
public:
	ListComponent();
	~ListComponent();

	int columnSize; //use to find out how many elements in struct


	void pause();
	void enable();
	void resume();
	void filter();
	void disable();
	void selected();
	void scrolled();
	void selectAll();
	void removeSort();
	void selectItem(int row);
	void sortColumn(int col);
	int64_t getNumSelected();
	void columnClicked(int col);
	uint32_t getBackgroundColour();
	void setItemCount(int64_t count);
	void setCaller(ListCaller* caller);
	void keyPressed(NMLVKEYDOWN* pnkd);
	INT_PTR drawing(HDC deviceContext);
	void populating(NMLVDISPINFO* plvdi);
	void setBackgroundColour(uint32_t colour);
	void rightClicked(int mouseX, int mouseY);
	int createItem(int index, const char * text);
	void setFont(int size, int weight, const char* fontface);
	int createColumn(int column, std::string Text, int width);
	int createSubItem(int index, int column, const char* text);
	void create(HWND parent, Dimensions dimensions, Origin origin);
	void createExt(HWND parent, Dimensions dimensions, Origin origin, ExtListCaller* extCaller);
};