#include "interface/gui/GUI.h"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {
	GUI gui = GUI(hInst);
	gui.run("Decima Explorer", "2.5");
}