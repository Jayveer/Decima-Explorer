#include "TextFieldComponent.h"

TextfieldComponent::TextfieldComponent() {
	setType(TEXTFIELD);
}

TextfieldComponent::~TextfieldComponent() {
}

INT_PTR TextfieldComponent::drawing(HDC deviceContext) {
	caller->textfieldDrawing(getHandle(), deviceContext);
	HBRUSH brush = createBrush(getBackgroundColour());
	return (INT_PTR)brush;
}

uint32_t TextfieldComponent::getBackgroundColour() {
	return backgroundColour;
}

void TextfieldComponent::setCaller(TextfieldCaller* caller) {
	this->caller = caller;
}

void TextfieldComponent::setBackgroundColour(uint32_t colour) {
	this->backgroundColour = colour;
}

void TextfieldComponent::create(HWND parent, Dimensions dimensions, Origin origin) {
	setParent(parent);
	DWORD style = WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER | WS_EX_CLIENTEDGE | ES_READONLY;
	HWND hwnd = CreateWindow("edit", text.c_str(), style, origin.x, origin.y, dimensions.width, dimensions.height, parent, NULL, NULL, this);
	setHandle(hwnd);
	SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)this);
}

void TextfieldComponent::setText(std::string text) {
	this->text = text;
	SendMessage(getHandle(), WM_SETTEXT, NULL, (LPARAM)this->text.c_str());
}

std::string TextfieldComponent::getText() {
	char buffer[MAX_PATH];
	GetWindowText(getHandle(), buffer, 1024);
	return buffer;
}

void TextfieldComponent::update() {
	RECT rect;
	GetClientRect(getHandle(), &rect);
	InvalidateRect(getHandle(), &rect, TRUE);
	MapWindowPoints(getHandle(), parent, (POINT*)&rect, 2);
	RedrawWindow(parent, &rect, NULL, RDW_ERASE | RDW_INVALIDATE);
}

void TextfieldComponent::setFont(int size, int weight, const char* fontface) {
	HFONT font = CreateFont(size, 0, 0, 0, weight, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, fontface);
	resources.push_back(font);
	SendMessage(getHandle(), WM_SETFONT, WPARAM(font), TRUE);
}
