#include "interface/cli/CLI.h"

int main(int argc, char **argv) {
	CLI cli = CLI(argc, argv);
	cli.run("Decima Explorer", "2.2");
}