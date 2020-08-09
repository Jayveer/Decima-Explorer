#include "GUI.h"

GUI::GUI(HINSTANCE hInst) {
	mainWindow.create(hInst, this, NULL, 0xD3D3D3);
	browseButton.setCaller(this);
	browserView.setCaller(this);
	fileList.setCaller(this);
	textbox.setCaller(this);
	extractButton.setCaller(this);
	footerView.setCaller(this);
}

GUI::~GUI() {
	
}

void GUI::textfieldDrawing(HWND hwnd, HDC deviceContext) {
	if (hwnd == textbox.getHandle()) {
		SetTextColor(deviceContext, RGB(144, 143, 168));
		SetBkColor(deviceContext, RGB(240, 240, 240));
	}
}

void GUI::listRightClicked(HWND hwnd, int mouseX, int mouseY) {
	if (hwnd == fileList.getHandle()) {
		if (fileList.getNumSelected()) {
			HMENU m_hMenu = CreatePopupMenu();
			InsertMenu(m_hMenu, 0, MF_BYCOMMAND | MF_STRING | MF_ENABLED, 1, "Extract Selected");
			int clicked = TrackPopupMenu(m_hMenu, TPM_TOPALIGN | TPM_LEFTALIGN | TPM_RETURNCMD, mouseX, mouseY, 0, hwnd, NULL);
			if (clicked) buttonPressed(extractButton.getHandle());
		}
	}
}

void GUI::listSelected(HWND hwnd) {
	fileList.getNumSelected() ? extractButton.enable() : extractButton.disable();
}

void GUI::viewDrawing(HWND hwnd) {}

void GUI::buttonDrawing(HWND hwnd) {}

void GUI::resetData() {
	if (sbuf) {
		delete sbuf;
		sbuf = NULL;
	}

	if (prefetchStream) {
		delete prefetchStream;
		prefetchStream = NULL;
	}

	DestroyWindow(fileList.getHandle());
	fileList.setHandle(NULL);

	prefetchData.clear();
}

void GUI::directoryChosen(std::string directory) {
	textbox.setText(directory);
	resetData();

	BinInitial initial(directory);
	if (!initial.open()) return;

	CorePrefetch prefetch;
	prefetchData = initial.extractFile(prefetch.getFilename());
	if (prefetchData.empty()) return;

	if (!fileList.getHandle()) {
		initFileList(mainWindow.getHandle());
		initExtractButton(mainWindow.getHandle());
		extractButton.disable();
	}

	sbuf = new membuf((char*)&prefetchData[0], prefetchData.size());
	
	prefetchStream = new std::istream(sbuf);
	prefetchStream->seekg(0x1C, SEEK_CUR);
	addFilesToRows();
}

void GUI::saveDirectoryChosen(std::string directory) {
	int64_t pos = -1;
	ProgressComponent pc;
	pc.create(mainWindow.getHandle(), { 1280, 35 }, { 0, 647 });
	pc.setRange(fileList.getNumSelected());
	pc.setIncrement();
	do {
		char file[MAX_PATH];
		pos = ListView_GetNextItem(fileList.getHandle(), pos, LVNI_SELECTED);
		if (pos == -1) break;
		ListView_GetItemText(fileList.getHandle(), pos, 0, file, MAX_PATH);
		std::thread thread(&GUI::directoryExtract, this, file, std::ref(directory), textbox.getText());
		pc.increment();
		thread.join();
	} while (pos != -1);

	MessageBox(mainWindow.getHandle(), "Selected files extracted successfully", "Done", MB_OK);
}

void GUI::directoryExtract(std::string filename, std::string output, std::string fileDirectory) {
	bool found = 0;

	output += "\\/" + filename;
	std::string path = getFilePathWithoutName(output);
	if (path != "") createDirectoriesFromPath(path);

	std::vector<std::string> files = getFilesFromDirectory(fileDirectory, ".bin");

	for (int i = 0; i < files.size(); i++) {
		ArchiveBin decimaArchive(files[i].c_str());
		if (!decimaArchive.open()) continue;
		found = decimaArchive.extractFile(filename, output, 1);
		if (found) break;
	}

}

void GUI::addFilesToRows() {
	SendMessage(fileList.getHandle(), WM_SETREDRAW, FALSE, 0);

	uint32_t prefetchSize;
	prefetchStream->read((char*)&prefetchSize, 4);

	for (int i = 0; i < prefetchSize; i++) {
		uint32_t size, hash;
		prefetchStream->read((char*)&size, 4);
		prefetchStream->read((char*)&hash, 4);
		std::string str;
		str.resize(size);
		prefetchStream->read((char*)str.c_str(), size);
		fileList.createItem(i, str.c_str());
	}

	uint32_t numSizes;
	prefetchStream->read((char*)&numSizes, 4);

	for (int i = 0; i < numSizes; i++) {
		uint32_t size;
		prefetchStream->read((char*)&size, 4);
		std::string fsize = std::to_string(byteToKiloByte(size)) + " KB";
		fileList.createSubItem(i, 1, fsize.c_str());
	}
	
	SendMessage(fileList.getHandle(), WM_SETREDRAW, TRUE, 0);

	delete prefetchStream;
	prefetchStream = NULL;
	delete sbuf;
	sbuf = NULL;
}

void GUI::listScrolled(HWND hwnd) { }

void GUI::buttonPressed(HWND hwnd) {
	FileComponent fc;
	fc.create(mainWindow.getHandle());
	std::string directory = fc.getFilename();
	if (directory == "") return;
	hwnd == browseButton.getHandle() ? directoryChosen(directory) : saveDirectoryChosen(directory);
}

void GUI::initFileList(HWND parent) {
	fileList.create(parent, { 1263, 430 }, { 0, 217 });
	fileList.createColumn(0, "Name", 1000);
	fileList.createColumn(1, "Size", 246);
}

void GUI::initBrowseButton(HWND parent) {
	browseButton.create(parent, "Browse", { 98, 20 }, { 1150, 187 });
	browseButton.setFont(15, FW_MEDIUM, "MS Shell Dlg 2");
	browseButton.setBackgroundColour(0xD7C8C1);
}

void GUI::initExtractButton(HWND parent) {
	extractButton.create(parent, "Extract", { 98, 20 }, { 1150, 654 });
	extractButton.setFont(15, FW_MEDIUM, "MS Shell Dlg 2");
	extractButton.setBackgroundColour(0xd3d3d3);
}

void GUI::initFooterView(HWND parent) {
	footerView.create(parent, { 1280, 35 }, { 0, 647 });
	footerView.setBackgroundColour(0xd3d3d3);
}

void GUI::initBrowserView(HWND parent) {
	header.create(parent, { 1280, 177 }, { 0, 0 }, "res/dexbg_l.bmp");
	browserView.create(parent, { 1280, 40 }, { 0, 177 });
	browserView.setBackgroundColour(0xD7C8C1);
}

void GUI::initTextbox(HWND parent) {
	textbox.text = "Select Data Directory Folder";
	textbox.create(parent, { 1130, 18 }, { 10, 187 });
	textbox.setFont(13, FW_MEDIUM, "MS Shell Dlg 2");
	textbox.setBackgroundColour(0xf0f0f0);
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