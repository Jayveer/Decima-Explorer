#include "CorePrefetch.h"

CorePrefetch::CorePrefetch() {
	setFilename(this->filename);
}

CorePrefetch::~CorePrefetch() {
}

void CorePrefetch::parse(std::istream& f) {
	parseHeader(f);
	parseStrings(f);
	parseSizes(f);
	parseIndex(f);
}

void CorePrefetch::parseHeader(std::istream& f) {
	f.read((char*)&prefetch.header.unknown,  8);
	f.read((char*)&prefetch.header.size, 4);
	f.read((char*)&prefetch.header.filetype, 16);
}

void CorePrefetch::parseStrings(std::istream& f) {
	f.read((char*)&prefetch.numStrings, 4);

	for (int i = 0; i < prefetch.numStrings; i++) {
		DecimaPrefetchString stringInfo;
		f.read((char*)&stringInfo.size, 4);
		f.read((char*)&stringInfo.hash, 4);

		stringInfo.string.resize(stringInfo.size);
		f.read((char*)stringInfo.string.c_str(), stringInfo.size);

		prefetch.strings.push_back(stringInfo);
	}
}

void CorePrefetch::parseSizes(std::istream& f) {
	f.read((char*)&prefetch.numSizes, 4);

	for (int i = 0; i < prefetch.numSizes; i++) {
		uint32_t filesize;
		f.read((char*)&filesize, 4);
		prefetch.filesizes.push_back(filesize);
	}
}

void CorePrefetch::parseIndex(std::istream& f) {
	f.read((char*)&prefetch.numIndex, 4);

	for (int i = 0; i < prefetch.numIndex; i++) {
		uint32_t index;
		f.read((char*)&index, 4);
		prefetch.indices.push_back(index);
	}
}

void CorePrefetch::extractFileTable() {
	std::ofstream out("file_list.txt");

	for (int i = 0; i < prefetch.strings.size(); i++) {
		out << prefetch.strings[i].string + "\n";
	}

	out.close();
}

void CorePrefetch::extractFileTableStreamed(DataBuffer data) {
	membuf sbuf((char*)&data[0], data.size());
	std::istream f(&sbuf);

	parseHeader(f);
	std::ofstream out("file_list.txt");
	f.read((char*)&prefetch.numStrings, 4);

	for (int i = 0; i < prefetch.numStrings; i++) {
		uint32_t size, hash;
		f.read((char*)&size, 4);
		f.read((char*)&hash, 4);
		std::string str;
		str.resize(size);
		f.read((char*)str.c_str(), size);
		out << str + "\n";
	}

	out.close();
}