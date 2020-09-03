#include "CorePrefetch.h"

CorePrefetch::CorePrefetch() {
	setFilename(this->filename);
}

CorePrefetch::~CorePrefetch() {
	//for (int i = 0; i < prefetch.numStrings; i++) {
		//delete[] prefetch.strings[i].string;
	//}
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
		//char *str = new char[stringInfo.size + 1];
		//f.read(str, stringInfo.size);
		//str[stringInfo.size] = '\0';
		//stringInfo.string = str;
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
	std::ofstream out("file_list.txt", std::ios::binary);
	uint16_t newLine = 0x0A0D;

	for (int i = 0; i < prefetch.strings.size(); i++) {
		const char* str = prefetch.strings[i].string.c_str();
		uint32_t size = prefetch.strings[i].string.size();
		out.write(str, size);
		out.write((char *)&newLine, 2);
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