#pragma once

#include "Datas.hpp"

class AssetManager {
public:
	AssetManager();
	~AssetManager() = default;

private:
	void loadAssetsFromFiles();
};
