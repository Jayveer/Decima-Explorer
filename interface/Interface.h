#pragma once
#include <mutex>

#include "../decima/file/prefetch/CorePrefetch.h"
#include "../decima/archive/mpk/ArchiveMoviePack.h"
#include "../decima/archive/bin/initial/BinInitial.h"
#include "../utils/Arrayutils.h"
#include "../utils/NumUtils.h"

class Interface {
private:
	int32_t progressNum;
	std::mutex* progressMutex;
public:
	Interface();
	~Interface();
	void pack(const std::string& filename, const std::string& directory);
	void repack(const std::string& filename, const std::string& directory);
};