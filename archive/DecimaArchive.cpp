#include "DecimaArchive.h"


DecimaArchive::DecimaArchive(std::string filename, std::string extension) {
	setFilename(filename);
}

DecimaArchive::~DecimaArchive() {
}

bool DecimaArchive::isEncrypted() {
	return getMagic() & 0x0F000000;
}

void DecimaArchive::setFilename(std::string Filename) {
	this->filename = Filename; 
}

std::string DecimaArchive::getFilename() { 
	return this->filename; 
}

std::string DecimaArchive::getExtension() {
	return this->extension;
}

void DecimaArchive::setSaltA(uint32_t* salt) {
	std::copy(salt, salt + 4, saltA);
}

void DecimaArchive::setSaltB(uint32_t* salt) {
	std::copy(salt, salt + 4, saltB);
}

void DecimaArchive::decrypt(uint32_t key, uint32_t key2, uint32_t* src) {
	decrypt(key, src);
	decrypt(key2, src + 4);
}

void DecimaArchive::decrypt(uint32_t key, uint32_t* src) {
	uint32_t iv[4];
	uint32_t inputKey[4] = { key, saltA[1], saltA[2], saltA[3] };
	MurmurHash3_x64_128(inputKey, 0x10, seed, iv);

	for (int i = 0; i < 4; i++) {
		src[i] ^= iv[i];
	}
}

void DecimaArchive::dataCipher(uint32_t* key, uint8_t* src, int size) {
	uint32_t iv[4];
	MurmurHash3_x64_128(key, 0x10, seed, iv);

	for (int i = 0; i < 4; i++) {
		iv[i] ^= saltB[i];
	}

	md5_byte_t* digest = md5Hash((md5_byte_t*)iv, 16);

	for (int i = 0; i < size; i++) {
		src[i] ^= digest[i % 16];
	}
}

int DecimaArchive::writeDataToFile(DataBuffer data, std::string filename) {
	FILE* f;
	fopen_s(&f, filename.c_str(), "wb");

	if (!f) {
		showError(WRITEFAIL);
		return 0;
	}

	fseek(f, 0, SEEK_END);
	fwrite(&data[0], 1, data.size(), f);
	fclose(f);
}

uint64_t DecimaArchive::getFileHash(std::string filename) {
	uint64_t hash;
	uint8_t byte[16];
	MurmurHash3_x64_128(filename.c_str(), filename.size() + 1, seed, &byte);
	memcpy(&hash, byte, 8);
	return hash;
}

