#pragma once
#include <vector>

inline
void deletePointerBuffer(std::vector<char*> pointerBuffer) {
	for (int i = 0; i < pointerBuffer.size(); i++) {
		delete pointerBuffer[i];
	}
}