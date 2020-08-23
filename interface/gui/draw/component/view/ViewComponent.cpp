#include "ViewComponent.h"
#include "..\file\FileComponent.h"

ViewComponent::ViewComponent() {
	setType(VIEW);
}

ViewComponent::~ViewComponent() {
}

void ViewComponent::create(HWND parent, Dimensions dimensions, Origin origin) {
	setParent(parent);
	DWORD style = WS_VISIBLE | WS_CHILD;
	HWND hwnd = CreateWindow("static", NULL, style, origin.x, origin.y, dimensions.width, dimensions.height, parent, NULL, NULL, this);
	setHandle(hwnd);
	SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)this);
}

INT_PTR ViewComponent::drawing() {
	caller->viewDrawing(getHandle());
	HBRUSH brush = createBrush(getBackgroundColour());
	return (INT_PTR)brush;
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