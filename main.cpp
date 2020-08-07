#include "cli/CLI.h"

int main(int argc, char **argv) {
	CLI cli = CLI(argc, argv);
	cli.run("Decima Explorer", "1.6");
}