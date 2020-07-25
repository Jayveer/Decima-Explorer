#include "hash/MurmurHash3.h"
#include "cli\CLI.h"
#include "archive/mpk/ArchiveMoviePack.h"

int main(int argc, char **argv) {
	CLI cli = CLI(argc, argv);
	cli.run("Decima Explorer");
}