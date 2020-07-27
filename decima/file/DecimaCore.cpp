#include "DecimaCore.h"

DecimaCore::DecimaCore() {

}

DecimaCore::DecimaCore(std::string filename) {

}

DecimaCore::~DecimaCore() {

}

void DecimaCore::open(DataBuffer data) {
	membuf sbuf((char*)&data[0], data.size());
	std::istream f(&sbuf);
	parse(f);
}

void DecimaCore::open(std::string filename) {
	std::ifstream ifs;
	ifs.open(filename, std::ifstream::binary);
	parse(ifs);
}