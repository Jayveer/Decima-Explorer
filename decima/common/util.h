#pragma once
#include <string>

#include "../../hash/MurmurHash3.h"


const uint8_t seed = 42;

inline
uint64_t getFileHash(const std::string& filename) {
	uint64_t hash;
	uint8_t byte[16];
	MurmurHash3_x64_128(filename.c_str(), filename.size() + 1, seed, &byte);
	memcpy(&hash, byte, 8);
	return hash;
}