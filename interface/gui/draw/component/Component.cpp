#include "Component.h"

Component::Component(bool registerClass) {
}

Component::~Component() {
	for (int i = 0; i < resources.size(); i++) {
		DeleteObject(resources[i]);
	}
	DestroyWindow(handle);
}

HWND Component::getHandle() {
	return handle;
}

void Component::setHandle(HWND inHandle) {
	handle = inHandle;
}

ComponentType Component::getType() {
	return this->componentType;
}

void Component::setType(ComponentType type) {
	this->componentType = type;
}

HWND Component::getParent() {
	return parent;
}

void Component::setParent(HWND inParent) {
	parent = inParent;
}

Origin Component::getOrigin() {
	RECT rect;
	GetWindowRect(handle, &rect);
	return { rect.left, rect.top };
}

Dimensions Component::getDimensions() {
	RECT rect;
	GetWindowRect(handle, &rect);
	return { (rect.top - rect.bottom), (rect.right - rect.left) };
}

HBRUSH Component::createBrush(uint32_t rgb) {
	rgb = _byteswap_ulong(rgb) >> 8;
	HBRUSH brush = CreateSolidBrush(rgb);
	resources.push_back(brush);
	return brush;
}