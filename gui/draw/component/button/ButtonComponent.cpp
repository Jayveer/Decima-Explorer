#include "ButtonComponent.h"

ButtonComponent::ButtonComponent() {
	setType(BUTTON);
}

ButtonComponent::~ButtonComponent() {

}

void ButtonComponent::setCaller(ButtonCaller *caller) {
	this->caller = caller;
}

void ButtonComponent::create(HWND parent, const char *name, Dimensions dimensions, Origin origin) {
	setParent(parent);
	DWORD style = WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON;
	HWND hwnd = CreateWindow("Button", name, style, origin.x, origin.y, dimensions.width, dimensions.height, parent, NULL, NULL, this);
	setHandle(hwnd);
	SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)this);
}

void ButtonComponent::setFont(int size, int weight, const char* fontface) {
	HFONT font = CreateFont(size, 0, 0, 0, weight, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, fontface);
	resources.push_back(font);
	SendMessage(getHandle(), WM_SETFONT, WPARAM(font), TRUE);
}

INT_PTR ButtonComponent::drawing() {
	caller->buttonDrawing(getHandle());
	HBRUSH brush = createBrush(getBackgroundColour());
	return (INT_PTR)brush;
}

void ButtonComponent::disable() {
	EnableWindow(getHandle(), false);
}

void ButtonComponent::enable() {
	EnableWindow(getHandle(), true);
}

void ButtonComponent::clicked() {
	caller->buttonPressed(getHandle());
}

void ButtonComponent::setBackgroundColour(uint32_t colour) {
	this->backgroundColour = colour;
}

uint32_t ButtonComponent::getBackgroundColour() {
	return this->backgroundColour;
}