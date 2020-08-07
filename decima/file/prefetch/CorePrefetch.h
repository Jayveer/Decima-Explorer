#pragma once
#include "../DecimaCore.h"


typedef struct DecimaPrefetchHeader {
	uint64_t unknown;
	uint32_t size;
	char filetype[16];
};

typedef struct DecimaPrefetchString {
	uint32_t size;
	uint32_t hash;
	std::string string;
};

typedef struct DecimaPrefetch {
	DecimaPrefetchHeader header;
	uint32_t numStrings;
	std::vector<DecimaPrefetchString> strings;
	uint32_t numSizes;
	std::vector<uint32_t> filesizes;
	uint32_t numIndex;
	std::vector<uint32_t> indices;
};


class CorePrefetch: public DecimaCore {
private:
	DecimaPrefetch prefetch;
	std::string filename = "prefetch/fullgame.prefetch.core";

	void parse(std::istream& f);
	void parseIndex(std::istream& f);
	void parseSizes(std::istream& f);
	void parseHeader(std::istream& f);
	void parseStrings(std::istream& f);
public:
	CorePrefetch();
	~CorePrefetch();
	
	
	void extractFileTable();
	void extractFileTableStreamed(DataBuffer data);
};