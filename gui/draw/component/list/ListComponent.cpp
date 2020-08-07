#include "ListComponent.h"

ListComponent::ListComponent() {
	setType(LISTVIEW);
}

ListComponent::~ListComponent() {
}

INT_PTR ListComponent::drawing(HDC deviceContext) {
	HBRUSH brush = createBrush(getBackgroundColour());
	return (INT_PTR)brush;
}

uint32_t ListComponent::getBackgroundColour() {
	return this->backgroundColour;
}

void ListComponent::setCaller(ListCaller* caller) {
	this->caller = caller;
}

void ListComponent::setBackgroundColour(uint32_t colour) {
	this->backgroundColour = colour;
}

void ListComponent::rightClicked(int mouseX, int mouseY) {
	caller->listRightClicked(getHandle(), mouseX, mouseY);
}

int ListComponent::getNumSelected() {
	return ListView_GetSelectedCount(getHandle());
	/*
	// Get the first selected item
		int iPos = ListView_GetNextItem(hListView, -1, LVNI_SELECTED);
		while (iPos != -1) {
    // iPos is the index of a selected item
    // do whatever you want with it

    // Get the next selected item
    iPos = ListView_GetNextItem(hListView, iPos, LVNI_SELECTED);
}
	*/
}

void ListComponent::selected() {
	caller->listSelected(getHandle());
}

void ListComponent::setFont(int size, int weight, const char* fontface) {
	HFONT font = CreateFont(size, 0, 0, 0, weight, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, fontface);
	resources.push_back(font);
	SendMessage(getHandle(), WM_SETFONT, WPARAM(font), TRUE);
}

int ListComponent::createItem(int index, const char* text) {
	LVITEM lvi = { 0 };
	lvi.iItem = index;
	lvi.iIndent = 0;
	int f = LVCFMT_LINE_BREAK;
	lvi.piColFmt = &f;
	lvi.mask = LVIF_TEXT | LVCF_WIDTH;
	lvi.pszText = const_cast<LPSTR>(text);
	lvi.iSubItem = 0;

	return ListView_InsertItem(getHandle(), &lvi);
}

int ListComponent::createSubItem(int index, int column, const char* text) {
	LVITEM lvi = { 0 };
	lvi.iItem = index;
	lvi.mask = LVIF_TEXT;
	lvi.pszText = const_cast<LPSTR>(text);
	lvi.iSubItem = column;

	return ListView_SetItem(getHandle(), &lvi);
}

void ListComponent::scrolled() {
	caller->listScrolled(getHandle());
}


int ListComponent::createColumn(int iCol, std::string text, int width) {
	LVCOLUMN lvc;
	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvc.fmt = LVCFMT_LEFT;
	lvc.cx = width;
	lvc.pszText = const_cast<LPSTR>(text.c_str());
	lvc.iSubItem = iCol;
	return ListView_InsertColumn(getHandle(), iCol, &lvc);
}

//fix bug with creating again when selecting file
void ListComponent::create(HWND parent, Dimensions dimensions, Origin origin) {
	setParent(parent);
	DWORD style = WS_VISIBLE | WS_CHILD | LVS_REPORT | WS_VSCROLL;
	HWND hwnd = CreateWindow(WC_LISTVIEW, "", style, origin.x, origin.y, dimensions.width, dimensions.height, parent, NULL, NULL, this);
	setHandle(hwnd);
	SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)this);
	uint32_t rgb = 0xf0f0f0;
	rgb = _byteswap_ulong(rgb) >> 8;
	ListView_SetTextBkColor(hwnd, rgb);
	ListView_SetBkColor(hwnd, rgb);
	ListView_SetExtendedListViewStyle(hwnd, LVS_EX_FULLROWSELECT);
}