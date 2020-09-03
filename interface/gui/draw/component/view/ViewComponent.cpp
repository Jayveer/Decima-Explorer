#include "ViewComponent.h"
#include "..\file\FileComponent.h"

ViewComponent::ViewComponent() {
	setType(VIEW);
}

ViewComponent::~ViewComponent() {
}

void ViewComponent::create(HWND parent, Dimensions dimensions, Origin origin, DWORD extraStyle) {
	setParent(parent);
	DWORD style = WS_VISIBLE | WS_CHILD | extraStyle;
	HWND hwnd = CreateWindow("static", NULL, style, origin.x, origin.y, dimensions.width, dimensions.height, parent, NULL, NULL, this);
	setHandle(hwnd);
	SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)this);
	SetWindowLong(hwnd, GWL_EXSTYLE, WS_EX_TOPMOST);
}

INT_PTR ViewComponent::drawing(HDC deviceContext) {
	caller->viewDrawing(getHandle(), deviceContext);
	HBRUSH brush = createBrush(getBackgroundColour());
	return (INT_PTR)brush;
}

void ViewComponent::clicked() {
	this->caller->viewClicked(getHandle());
}

void ViewComponent::setBackgroundColour(uint32_t colour) {
	this->backgroundColour = colour;
}

uint32_t ViewComponent::getBackgroundColour() {
	return this->backgroundColour;
}

void ViewComponent::setCaller(ViewCaller* caller) {
	this->caller = caller;
}

void ViewComponent::setFont(int size, int weight, const char* fontface) {
	HFONT font = CreateFont(size, 0, 0, 0, weight, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, fontface);
	resources.push_back(font);
	SendMessage(getHandle(), WM_SETFONT, WPARAM(font), TRUE);
}