#pragma once
#include <string>
#include <math.h>

inline
int byteToKiloByte(int bytes) {
	return bytes % 1024 ? (bytes / 1024) + 1 : bytes / 1024;
}