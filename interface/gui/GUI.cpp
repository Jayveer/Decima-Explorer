#include "GUI.h"

GUI::GUI(HINSTANCE hInst) {
	HICON icon = fetchIcon(DEX_L_ICO, DEX_L_ICO_COMPRESSED_SIZE, DEX_L_ICO_UNCOMPRESSED_SIZE, 128, 128);
	HICON iconSm = fetchIcon(DEX_S_ICO, DEX_S_ICO_COMPRESSED_SIZE, DEX_S_ICO_UNCOMPRESSED_SIZE, 16, 16);

	mainWindow.create(hInst, this, NULL, icon, iconSm, 0xD3D3D3);
	browseButton.setCaller(this);
	browserView.setCaller(this);
	fileList.setCaller(this);
	browseTextbox.setCaller(this);
	extractButton.setCaller(this);
	footerView.setCaller(this);
	filterTextbox.setCaller(this);
	closeFilterButton.setCaller(this);
}

GUI::~GUI() {
}

void GUI::showError(const char* message) {
	MessageBox(mainWindow.getHandle(), message, "Decima Explorer", MB_OK | MB_ICONERROR);
}

void GUI::showWarning(const char* message) {
	MessageBox(mainWindow.getHandle(), message, "Decima Explorer", MB_OK | MB_ICONWARNING);
}

void GUI::showMessage(const char* message) {
	MessageBox(mainWindow.getHandle(), message, "Decima Explorer", MB_OK);
}

void GUI::addFileInfo(const char* name, uint32_t size) {
	FileInfo fi = { name, size };
	fileInfo.push_back(fi);
}

#if PACKER
void GUI::populateFileInfo(const std::string& filter) {
	for (int i = 0; i < files.size(); i++) {
		if (files[i].find(filter) == std::string::npos) continue;
		addFileInfo(files[i].c_str(), 0);
	}
}
#else
void GUI::populateFileInfo(const std::string& filter) {
	for (int i = 0; i < prefetchFile.getPrefetch()->numStrings; i++) {
		if(prefetchFile.getPrefetch()->strings[i].string.find(filter) == std::string::npos) continue;
		addFileInfo(prefetchFile.getPrefetch()->strings[i].string.c_str(), prefetchFile.getPrefetch()->filesizes[i]);
	}
}
#endif

void GUI::filterList(const std::string& filter) {
	fileInfo.clear();
	populateFileInfo(filter);
	fileList.removeSort();
	fileList.setItemCount(fileInfo.size());
}

void GUI::textfieldChanged(HWND hwnd) {
	if (hwnd == filterTextbox.getHandle()) filterList(filterTextbox.getText());
}

void GUI::columnSortAscending(HWND hwnd, int col) {
	std::sort(fileInfo.begin(), fileInfo.end(), [col](FileInfo lhs, FileInfo rhs) {
		return col ? lhs.size > rhs.size : strcmp(lhs.file, rhs.file) > 0;
	});
	fileList.setItemCount(fileInfo.size());
}

void GUI::columnSortDescending(HWND hwnd, int col) {
	std::sort(fileInfo.begin(), fileInfo.end(), [col](FileInfo lhs, FileInfo rhs) {
		return col ? lhs.size < rhs.size : strcmp(lhs.file, rhs.file) < 0;
	});
	fileList.setItemCount(fileInfo.size());
}

void GUI::addFilesToRows() {
	DecimaPrefetch* prefetch = prefetchFile.getPrefetch();
	fileList.setItemCount(prefetch->numStrings);
}

void GUI::update() {
	checkQueue();
}

void GUI::intervalUpdate() {
	extractProgress.setValue(getProgress());
}

void GUI::exit() {
	PostQuitMessage(0);
}

void GUI::textfieldDrawing(HWND hwnd, HDC deviceContext) {
	if (hwnd == browseTextbox.getHandle()) {
		SetTextColor(deviceContext, RGB(144, 143, 168));
		SetBkColor(deviceContext, RGB(240, 240, 240));
	}

	if (hwnd == filterTextbox.getHandle()) {
		SetTextColor(deviceContext, RGB(0, 0, 0));
		SetBkColor(deviceContext, RGB(240, 240, 240));
	}
}

void GUI::listRightClicked(HWND hwnd, int mouseX, int mouseY) {
	if (hwnd == fileList.getHandle()) {
		if (fileList.getNumSelected()) {
			HMENU m_hMenu = CreatePopupMenu();
			const char* text = isPacker ? "Pack Selected" : "Extract Selected";
			InsertMenu(m_hMenu, 0, MF_BYCOMMAND | MF_STRING | MF_ENABLED, 1, text);
			int clicked = TrackPopupMenu(m_hMenu, TPM_TOPALIGN | TPM_LEFTALIGN | TPM_RETURNCMD, mouseX, mouseY, 0, hwnd, NULL);
			if (clicked) buttonPressed(extractButton.getHandle());
		}
	}
}

void GUI::viewClicked(HWND hwnd) {
	if (hwnd == closeFilterButton.getHandle()) {
		deinitFilter();
		deinitCloseFilterButton();
	}
}

void GUI::listFilter(HWND hwnd) {
	openFilter();
}

void GUI::listSelected(HWND hwnd) {
	fileList.getNumSelected() ? extractButton.enable() : extractButton.disable();
}

void GUI::viewDrawing(HWND hwnd, HDC deviceContext) {
	if (hwnd == closeFilterButton.getHandle()) {
		SetBkColor(deviceContext, RGB(211, 211, 211));
	}
}

void GUI::listScrolled(HWND hwnd) {}
void GUI::columnClicked(HWND hwnd, int col) {}
void GUI::buttonDrawing(HWND hwnd, HDC deviceContext) {}

void GUI::listAddItem(HWND hwnd, LV_ITEM* item) {
	int itemid = item->iItem;
	if (item->iSubItem == 0) item->pszText = (LPSTR)fileInfo[itemid].file;
	if (item->iSubItem == 1) {
		std::string fsize = std::to_string(byteToKiloByte(fileInfo[itemid].size)) + " KB";
		const char* text = fsize.c_str();
		lstrcpyn(item->pszText, text, item->cchTextMax);
	}
}

void GUI::resetData() {
	closeFilter();
	fileInfo.clear();
	fileMap.clear();
	deinitFileList();
	deinitPrefetch();
	deinitExtractButton();
}

void GUI::directoryChosen(std::string directory) {
	browseTextbox.setText(directory);
	resetData();
	if (isPacker) {
		files = getFiles(directory);
	} else {
		if (!initPrefetch(directory.c_str())) return;
	}
	populateFileInfo();
	initFileList(mainWindow.getHandle());
	initExtractButton(mainWindow.getHandle());
	extractButton.disable();
	int count = isPacker ? files.size() : prefetchFile.getPrefetch()->numStrings;
	fileList.setItemCount(count);
}

void GUI::checkQueue() {
	MSG msg;
	BOOL result;

	while (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) {
		switch (GetMessage(&msg, NULL, 0, 0)) {
		case 0: {
			this->forceQuit = true;
			return;
		} break;
		default: {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} break;
		}
	}
}

#if PACKER
std::vector<std::string> GUI::getSelectedStrings() {
	int64_t pos = -1;
	std::vector<std::string> selectedStrings;

	do {
		pos = ListView_GetNextItem(fileList.getHandle(), pos, LVNI_SELECTED);
		if (pos == -1) break;
		selectedStrings.push_back(files[pos]);
	} while (pos != -1);

	return selectedStrings;
}

void GUI::saveDirectoryChosen(std::string directory) {
	std::vector<std::string> selectedStrings = getSelectedStrings();
	extractProgress.create(mainWindow.getHandle(), { 1280, 35 }, { 0, 647 }, PBS_MARQUEE);
	extractProgress.setMarquee();
	disableElements();

	std::future<void> future = checkFileExists(directory) ?
		std::async(&GUI::repack, this, std::ref(selectedStrings), std::ref(directory), browseTextbox.getText()):
		std::async(&GUI::pack,   this, std::ref(selectedStrings), browseTextbox.getText(), std::ref(directory));

	while (!future._Is_ready()) checkQueue();
	enableElements();

	deinitExtractProgress();
	showMessage("Packing Finished");
}

#else
std::vector<char*> GUI::getSelectedStrings() {
	int64_t pos = -1;
	std::vector<char*> selectedStrings;

	do {
		char* file = new char[MAX_PATH];
		pos = ListView_GetNextItem(fileList.getHandle(), pos, LVNI_SELECTED);
		if (pos == -1) break;
		ListView_GetItemText(fileList.getHandle(), pos, 0, file, MAX_PATH);
		selectedStrings.push_back(file);
	} while (pos != -1);

	return selectedStrings;
}

void GUI::saveDirectoryChosen(std::string directory) {
	std::vector<char*> selectedStrings = getSelectedStrings();
	if (fileMap.empty()) buildFileMap(browseTextbox.getText().c_str());
	initExtractProgress(mainWindow.getHandle(), selectedStrings.size());
	disableElements();
	parallelExtract(directory, selectedStrings);
	deletePointerBuffer(selectedStrings);
	enableElements();
	deinitExtractProgress();
	showMessage("Extraction Finished");
}
#endif

HICON GUI::fetchIcon(const unsigned char* buffer, int bufferSize, int iconSize, int width, int height) {
	unsigned char* icon = new unsigned char[iconSize];
	int res = Kraken_Decompress(buffer, bufferSize, icon, iconSize);
	return CreateIconFromResourceEx((PBYTE)icon, iconSize, TRUE, 0x30000, width, height, LR_DEFAULTSIZE | LR_DEFAULTCOLOR | LR_SHARED);
	delete[] icon;
}

void GUI::disableElements() {
	fileList.disable();
	browseButton.disable();
	extractButton.disable();
}

void GUI::enableElements() {
	fileList.enable();
	browseButton.enable();
}


#if PACKER
void GUI::buttonPressed(HWND hwnd) {
	FileComponent fc;

	if (hwnd == browseButton.getHandle()) {
		DWORD options = fc.defaultOptions | FOS_PICKFOLDERS;
		fc.create(mainWindow.getHandle(), options);
	}

	if (hwnd == extractButton.getHandle()) {
		std::vector<FileFilter> filter = { {L"Decima Binary(*.bin)", L"*.bin"} };
		DWORD options = fc.defaultOptions & ~(FOS_FILEMUSTEXIST);
		fc.create(mainWindow.getHandle(), options, filter);
	}

	std::string directory = fc.getFilename();
	if (directory == "") return;
	hwnd == browseButton.getHandle() ? directoryChosen(directory) : saveDirectoryChosen(directory);
}

#else
void GUI::buttonPressed(HWND hwnd) {
	FileComponent fc;
	DWORD options = fc.defaultOptions | FOS_PICKFOLDERS;
	fc.create(mainWindow.getHandle(), options);
	std::string directory = fc.getFilename();
	if (directory == "") return;
	hwnd == browseButton.getHandle() ? directoryChosen(directory) : saveDirectoryChosen(directory);
}
#endif

void GUI::openFilter() {
	initFilter(mainWindow.getHandle());
	SetFocus(filterTextbox.getHandle());
	initCloseFilterButton(mainWindow.getHandle());
}

void GUI::closeFilter() {
	if (filterTextbox.getHandle()) {
		deinitFilter();
		deinitCloseFilterButton();
	}
}

void GUI::deinitExtractProgress() {
	this->progressNum = 0;
	DestroyWindow(extractProgress.getHandle());
	extractProgress.setHandle(NULL);
}

void GUI::initExtractProgress(HWND parent, int32_t size) {
	extractProgress.create(parent, { 1280, 35 }, { 0, 647 });
	extractProgress.setRange(size);
}

void GUI::deinitFileList() {
	DestroyWindow(fileList.getHandle());
	fileList.setHandle(NULL);
}

void GUI::initFileList(HWND parent) {
	fileList.createExt(parent, { 1263, 430 }, { 0, 217 }, this);
	fileList.createColumn(0, "Name", 1000);
	fileList.createColumn(1, "Size", 246);
}

void GUI::initBrowseButton(HWND parent) {
	browseButton.create(parent, "Browse", { 98, 20 }, { 1150, 187 });
	browseButton.setFont(15, FW_MEDIUM, "MS Shell Dlg 2");
	uint32_t colour = isPacker ? 0xE8E8E8 : 0xD7C8C1;
	browseButton.setBackgroundColour(colour);
}

void GUI::deinitExtractButton() {
	DestroyWindow(extractButton.getHandle());
	extractButton.setHandle(NULL);
}

void GUI::initExtractButton(HWND parent) {
	const char *text = isPacker ? "Pack" : "Extract";
	extractButton.create(parent, text, { 98, 20 }, { 1150, 654 });
	extractButton.setFont(15, FW_MEDIUM, "MS Shell Dlg 2");
	extractButton.setBackgroundColour(0xd3d3d3);
}

void GUI::initFooterView(HWND parent) {
	footerView.create(parent, { 1280, 35 }, { 0, 647 });
	footerView.setBackgroundColour(0xd3d3d3);
}

#if PACKER
void GUI::initBrowserView(HWND parent) {
	unsigned char* bitmap = new unsigned char[DEX_BG_DARK_UNCOMPRESSED_SIZE];
	int res = Kraken_Decompress(DEX_BG_DARK, DEX_BG_DARK_COMPRESSED_SIZE, bitmap, DEX_BG_DARK_UNCOMPRESSED_SIZE);
	header.create(parent, { 1280, 177 }, { 0, 0 }, bitmap);
	delete[] bitmap;
	browserView.create(parent, { 1280, 40 }, { 0, 177 });
	browserView.setBackgroundColour(0xe8e8e8);
}
#else
void GUI::initBrowserView(HWND parent) {
	unsigned char* bitmap = new unsigned char[DEX_BG_LIGHT_UNCOMPRESSED_SIZE];
	int res = Kraken_Decompress(DEX_BG_LIGHT, DEX_BG_LIGHT_COMPRESSED_SIZE, bitmap, DEX_BG_LIGHT_UNCOMPRESSED_SIZE);
	header.create(parent, { 1280, 177 }, { 0, 0 }, bitmap);
	delete[] bitmap;
	browserView.create(parent, { 1280, 40 }, { 0, 177 });
	browserView.setBackgroundColour(0xD7C8C1);
}
#endif

void GUI::deinitFilter() {
	filterTextbox.setText("");
	DestroyWindow(filterTextbox.getHandle());
	filterTextbox.setHandle(NULL);
}

void GUI::initFilter(HWND parent) {
	filterTextbox.create(parent, { 800, 18 }, { 1, 648 }, WS_EX_CLIENTEDGE);
	filterTextbox.setPlacheolderText(L"Filter");
	filterTextbox.setFont(13, FW_MEDIUM, "MS Shell Dlg 2");
	filterTextbox.setBackgroundColour(0xf0f0f0);
}

void GUI::deinitCloseFilterButton() {
	DestroyWindow(closeFilterButton.getHandle());
	closeFilterButton.setHandle(NULL);
}

void GUI::initCloseFilterButton(HWND parent) {
	closeFilterButton.create(parent, { 18, 18 }, { 806, 647 }, SS_NOTIFY);
	SetWindowText(closeFilterButton.getHandle(), "x");
	closeFilterButton.setBackgroundColour(0xd3d3d3);
	closeFilterButton.setFont(16, FW_MEDIUM, "MS Shell Dlg 2");
}

void GUI::initTextbox(HWND parent) {
	browseTextbox.text = "Select Data Directory Folder";
	browseTextbox.create(parent, { 1130, 18 }, { 10, 187 }, ES_READONLY | ES_CENTER | WS_BORDER | WS_EX_CLIENTEDGE);
	browseTextbox.setFont(13, FW_MEDIUM, "MS Shell Dlg 2");
	browseTextbox.setBackgroundColour(0xf0f0f0);
}

void GUI::windowCreated(HWND hwnd) {
	initBrowserView(hwnd);
	initBrowseButton(hwnd);
	initTextbox(hwnd);
}

void GUI::windowRightClicked(HWND hwnd, int mouseX, int mouseY) {
	HMENU m_hMenu = CreatePopupMenu();
	InsertMenu(m_hMenu, 0, MF_BYCOMMAND | MF_STRING | MF_ENABLED, 1, "About");
	int clicked = TrackPopupMenu(m_hMenu, TPM_TOPALIGN | TPM_LEFTALIGN | TPM_RETURNCMD, mouseX, mouseY, 0, hwnd, NULL);
	if (clicked) MessageBox(mainWindow.getHandle(), aboutText, "About", MB_OK);
}

void GUI::run(std::string programName, std::string version) {
	mainWindow.run(programName, version);
}