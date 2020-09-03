#pragma once
#include <vector>
#include <string>
#include <Windows.h>
#include <Commctrl.h>

struct Origin {
	LONG x;
	LONG y;
};

struct Dimensions {
	LONG width;
	LONG height;
};

enum ComponentType {
	VIEW,
	IMAGE,
	WINDOW,
	BUTTON,
	LISTVIEW,
	TEXTFIELD,
	INVALID
};

class ProcedureCaller {
public:
	virtual LRESULT ProcedureWrapper(HWND inHwnd, UINT message, WPARAM wParam, LPARAM lParam) = 0;
};

class Component {
public:
	HWND getHandle();
	HWND getParent();
	void setParent(HWND inParent);
	void setHandle(HWND inHandle);
	ComponentType getType();
	void setType(ComponentType);
	Origin getOrigin();
	Dimensions getDimensions();
protected:
	Component(bool registerClass = 0);
	~Component();

	HWND handle = {};
	HWND parent = {};
	ComponentType componentType;
	std::vector<HGDIOBJ> resources;

	
	virtual HBRUSH createBrush(uint32_t rgb);
};

/*
create
draw
remove
*/