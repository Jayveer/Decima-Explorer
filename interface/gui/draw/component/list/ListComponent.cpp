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

int64_t ListComponent::getNumSelected() {
	return ListView_GetSelectedCount(getHandle());
}

void ListComponent::selected() {
	caller->listSelected(getHandle());
}

void ListComponent::scrolled() {
	caller->listScrolled(getHandle());
}

void ListComponent::pause() {
	SendMessage(getHandle(), WM_SETREDRAW, FALSE, 0);
}

void ListComponent::resume() {
	SendMessage(getHandle(), WM_SETREDRAW, TRUE, 0);
}

void ListComponent::populating(NMLVDISPINFO* plvdi){
	LV_ITEM* pItem = &(plvdi)->item;
	int itemid = pItem->iItem;

	if (pItem->mask & LVIF_TEXT) this->extCaller->listAddItem(getHandle(), pItem);
}

void ListComponent::setItemCount(int64_t count) {
	ListView_SetItemCount(getHandle(), count);
}

void ListComponent::enable() {
	EnableWindow(getHandle(), true);
}

void ListComponent::disable() {
	EnableWindow(getHandle(), false);
}

void ListComponent::columnClicked(int col) {
	sortColumn(col);
}

void ListComponent::selectAll() {
	pause();
	int rows = ListView_GetItemCount(getHandle());
	for (int i = 0; i < rows; i++) {
		selectItem(i);
	}
	resume();
}

void ListComponent::selectItem(int row) {
	ListView_SetItemState(getHandle(), row, LVIS_FOCUSED | LVIS_SELECTED, 0x000F);
}

void ListComponent::filter() {
	if (extCaller) extCaller->listFilter(getHandle());
}

void ListComponent::keyPressed(NMLVKEYDOWN* pnkd) {
	if (GetKeyState(VK_CONTROL) & 0x8000) {
		if (pnkd->wVKey == 'F') filter();
		if (pnkd->wVKey == 'A') selectAll();
	}
}

void ListComponent::removeSort() {
	HDITEM  hdrItem = { 0 };
	hdrItem.mask = HDI_FORMAT;
	HWND header = ListView_GetHeader(getHandle());
	int numCol = Header_GetItemCount(header);
	for (int col = 0; col < numCol; col++) {
		Header_GetItem(header, col, &hdrItem);
		hdrItem.fmt = hdrItem.fmt & ~(HDF_SORTDOWN | HDF_SORTUP);
		Header_SetItem(header, col, &hdrItem);
	}
}

void ListComponent::sortColumn(int col) {
	HDITEM  hdrItem = { 0 };
	hdrItem.mask = HDI_FORMAT;
	HWND header = ListView_GetHeader(getHandle());
	Header_GetItem(header, col, &hdrItem);
	removeSort();

	switch (hdrItem.fmt & 0xF00) {
	default:
	case HDF_SORTDOWN:
		hdrItem.fmt = (hdrItem.fmt & ~HDF_SORTDOWN) | HDF_SORTUP;
		extCaller->columnSortDescending(getHandle(), col);
		break;
	case HDF_SORTUP:
		hdrItem.fmt = (hdrItem.fmt & ~HDF_SORTUP) | HDF_SORTDOWN;
		extCaller->columnSortAscending(getHandle(), col);
		break;
	}

	Header_SetItem(header, col, &hdrItem);
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

int ListComponent::createColumn(int iCol, std::string text, int width) {
	LVCOLUMN lvc;
	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvc.fmt = LVCFMT_LEFT;
	lvc.cx = width;
	lvc.pszText = const_cast<LPSTR>(text.c_str());
	lvc.iSubItem = iCol;
	return ListView_InsertColumn(getHandle(), iCol, &lvc);
}

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
	ListView_SetExtendedListViewStyle(hwnd, LVS_EX_FULLROWSELECT | LVS_EX_DOUBLEBUFFER);
}

void ListComponent::createExt(HWND parent, Dimensions dimensions, Origin origin, ExtListCaller* extCaller) {
	setParent(parent);
	DWORD style = WS_VISIBLE | WS_CHILD | LVS_REPORT | WS_VSCROLL | LVS_OWNERDATA;
	HWND hwnd = CreateWindow(WC_LISTVIEW, "", style, origin.x, origin.y, dimensions.width, dimensions.height, parent, NULL, NULL, this);
	setHandle(hwnd);
	SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)this);
	uint32_t rgb = 0xf0f0f0;
	rgb = _byteswap_ulong(rgb) >> 8;
	ListView_SetTextBkColor(hwnd, rgb);
	ListView_SetBkColor(hwnd, rgb);
	ListView_SetExtendedListViewStyle(hwnd, LVS_EX_FULLROWSELECT | LVS_EX_DOUBLEBUFFER);
	this->extCaller = extCaller;
}