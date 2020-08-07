#include "ImageComponent.h"

ImageComponent::ImageComponent() {
	setType(IMAGE);
}

ImageComponent::~ImageComponent() {

}

void ImageComponent::create(HWND parent, Dimensions dimensions, Origin origin, const char *imageFile) {
	setParent(parent);
	DWORD style = WS_VISIBLE | WS_CHILD | SS_BITMAP;
	HWND hwnd = CreateWindow("static", NULL, style, origin.x, origin.y, dimensions.width, dimensions.height, parent, NULL, NULL, this);
	setHandle(hwnd);
	SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)this);
	HBITMAP image = loadImage(imageFile);
	SendMessage(hwnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)image);
}

HBITMAP ImageComponent::loadImage(const char* imageFile) {
	HBITMAP image = (HBITMAP)LoadImage(NULL, imageFile, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	resources.push_back(image);
	return image;
}

INT_PTR ImageComponent::drawing() {
	if (caller) caller->viewDrawing(getHandle());
	HBRUSH brush = createBrush(getBackgroundColour());
	return (INT_PTR)brush;
}

void ImageComponent::setBackgroundColour(uint32_t colour) {
	this->backgroundColour = colour;
}

uint32_t ImageComponent::getBackgroundColour() {
	return this->backgroundColour;
}

void ImageComponent::setCaller(ImageCaller* caller) {
	this->caller = caller;
}

void ImageComponent::rightClicked(int mouseX, int mouseY) {
	int dummy = 0;
}
