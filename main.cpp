#include "hash/MurmurHash3.h"
#include "cli\CLI.h"
#include "decima/archive/mpk/ArchiveMoviePack.h"

int main(int argc, char **argv) {
	CLI cli = CLI(argc, argv);
	cli.run("Decima Explorer", "1.5");
}