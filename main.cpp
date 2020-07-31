#include "cli/CLI.h"
#include "gui/GUI.h"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {
	GUI gui = GUI(hInst);
	gui.run("Decima Explorer", "1.5");
}

/*
int main(int argc, char **argv) {
	CLI cli = CLI(argc, argv);
	cli.run("Decima Explorer", "1.5");
}
*/