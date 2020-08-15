#include "GUI.h"

GUI::GUI(HINSTANCE hInst) : progressMutex() {
	HICON icon = fetchIcon(DEX_L_ICO, DEX_L_ICO_COMPRESSED_SIZE, DEX_L_ICO_UNCOMPRESSED_SIZE, 128, 128);
	HICON iconSm = fetchIcon(DEX_S_ICO, DEX_S_ICO_COMPRESSED_SIZE, DEX_S_ICO_UNCOMPRESSED_SIZE, 16, 16);

	progressMutex = new std::mutex();
	mainWindow.create(hInst, this, NULL, icon, iconSm, 0xD3D3D3);
	browseButton.setCaller(this);
	browserView.setCaller(this);
	fileList.setCaller(this);
	textbox.setCaller(this);
	extractButton.setCaller(this);
	footerView.setCaller(this);
}

GUI::~GUI() {
	delete progressMutex;
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

	deinitFileList();
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

void GUI::batchExtract(const std::vector<char*>& filenames, std::string output, int batchSize, int batchOffset) {
	int step = batchSize < 10 ? 1 : batchSize / 10;

	for (int i = batchOffset; i < batchSize + batchOffset; i++) {
		directoryExtract(filenames[i], output);
		if ((i - batchOffset) % step == 0) updateProgress(step);
		if (this->forceQuit) return;
	}
	if (step != 1 ) updateProgress(batchSize % 10);
}

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

//TODO make dedicated thread handler class
void GUI::parallelExtract(const std::string& directory, const std::vector<char*>& selectedStrings) {
	uint32_t numThreads = std::thread::hardware_concurrency();
	if (!numThreads) numThreads = 2;

	uint32_t divvy = selectedStrings.size() / numThreads;
	uint32_t excess = selectedStrings.size() % numThreads; 
	uint16_t add = 0;

	if (!divvy) numThreads = excess;

	std::vector<std::future<void>> futures;

	for (int i = 0; i < numThreads; i++) {
		int batchSize = divvy;
		int batchOffset = i * divvy;

		if (i < excess) batchSize++;

		futures.push_back(std::async(std::launch::async, &GUI::batchExtract, this, std::ref(selectedStrings), std::ref(directory), batchSize, batchOffset + add));
		if (i < excess) add++;
	}

	int x = 0;
	for (int i = 0; i < futures.size(); i++) {
		while (!futures[i]._Is_ready()) {
			if (x % 10000 == 0) extractProgress.setValue(getProgress());
			checkQueue();
			x++;
		}
		extractProgress.setValue(getProgress());
	}

	if (this->forceQuit) PostQuitMessage(0);
}

void GUI::saveDirectoryChosen(std::string directory) {
	std::vector<char*> selectedStrings = getSelectedStrings();
	std::vector<char*> files = buildFileMap( textbox.getText().c_str() );	

	initExtractProgress(mainWindow.getHandle());
	disableElements();

	parallelExtract(directory, selectedStrings);

	deletePointerBuffer(selectedStrings);
	deletePointerBuffer(files);

	enableElements();
	deinitExtractProgress();
	MessageBox(mainWindow.getHandle(), "Selected files extracted successfully", "Done", MB_OK);
}

void GUI::directoryExtract(const char *filename, std::string output) {
	std::string fname = filename;
	if (!hasExtension(fname, "core")) addExtension(fname, "core");
	uint64_t hash = getFileHash(fname);
	const char* fd = fileMap[hash];
	if (fd == NULL) return;

	output += "\\/";
	output += filename;
	std::string path = getFilePathWithoutName(output);
	if (path != "") createDirectoriesFromPath(path);

	ArchiveBin decimaArchive(fd);
	if (!decimaArchive.open()) return;
	decimaArchive.extractFile(filename, output, 1);
}

std::vector<char *> GUI::buildFileMap(const char* fileDirectory) {
	std::vector<std::string> files = getFilesFromDirectory(fileDirectory, ".bin");
	std::vector<char*> savePointers;

	for (int i = 0; i < files.size(); i++) {
		ArchiveBin decimaArchive(files[i].c_str());
		if (!decimaArchive.open()) continue;

		std::vector <BinFileEntry> fileTable = decimaArchive.getFileTable();

		char* fileDir = new char[strlen(files[i].c_str()) + 1];
		strncpy(fileDir, files[i].c_str(), strlen(files[i].c_str()) + 1);
		savePointers.push_back(fileDir);

		for (int j = 0; j < fileTable.size(); j++) {
			fileMap[fileTable[j].hash] = fileDir;
		}
	}

	return savePointers;
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

HICON GUI::fetchIcon(const unsigned char* buffer, int bufferSize, int iconSize, int width, int height) {
	unsigned char* icon = new unsigned char[iconSize];
	int res = Kraken_Decompress(buffer, bufferSize, icon, iconSize);
	return CreateIconFromResourceEx((PBYTE)icon, iconSize, TRUE, 0x30000, width, height, LR_DEFAULTSIZE | LR_DEFAULTCOLOR | LR_SHARED);
	delete[] icon;
}

void GUI::disableElements() {
	EnableWindow(fileList.getHandle(), false);
	extractButton.disable();
	browseButton.disable();
}

void GUI::enableElements() {
	EnableWindow(fileList.getHandle(), true);
	browseButton.enable();
}

void GUI::updateProgress(int count) {
	progressMutex->lock();
	this->progressNum += count;
	progressMutex->unlock();
}

int32_t GUI::getProgress() {
	progressMutex->lock();
		int32_t pNum = progressNum;
	progressMutex->unlock();
	return pNum;
}

void GUI::buttonPressed(HWND hwnd) {
	FileComponent fc;
	fc.create(mainWindow.getHandle());
	std::string directory = fc.getFilename();
	if (directory == "") return;
	hwnd == browseButton.getHandle() ? directoryChosen(directory) : saveDirectoryChosen(directory);
}

void GUI::deinitExtractProgress() {
	this->progressNum = 0;
	DestroyWindow(extractProgress.getHandle());
	extractProgress.setHandle(NULL);
}

void GUI::initExtractProgress(HWND parent) {
	extractProgress.create(parent, { 1280, 35 }, { 0, 647 });
	extractProgress.setRange(fileList.getNumSelected());
}

void GUI::deinitFileList() {
	DestroyWindow(fileList.getHandle());
	fileList.setHandle(NULL);
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
	unsigned char *bitmap = new unsigned char[DEX_BG_LIGHT_UNCOMPRESSED_SIZE];
	int res = Kraken_Decompress(DEX_BG_LIGHT , DEX_BG_LIGHT_COMPRESSED_SIZE, bitmap, DEX_BG_LIGHT_UNCOMPRESSED_SIZE);
	header.create(parent, { 1280, 177 }, { 0, 0 }, bitmap);
	delete[] bitmap;
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