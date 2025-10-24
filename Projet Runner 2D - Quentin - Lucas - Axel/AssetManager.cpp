#include "AssetManager.hpp"

#include <iostream>

AssetManager::AssetManager() {
	loadAssetsFromFiles();
}

void AssetManager::loadAssetsFromFiles() {

	Shared::tileSetTexture.loadFromFile("Assets/tiles_map/RunnerTileSet.png");
	Shared::collectibleTexture.loadFromFile("Assets/Images/Gold.png");

	// --- BIOME 1 : facile ---
	Shared::backboardFirstTextureDifficultyOne.loadFromFile("Assets/tiles_map/backgroundFar.png");
	Shared::backboardSecondTextureDifficultyOne.loadFromFile("Assets/tiles_map/backgroundNear.png");

	// --- BIOME 2 : normal ---
	Shared::backboardFirstTextureDifficultyTwo.loadFromFile("Assets/tiles_map/backgroundFar_2.png");
	Shared::backboardSecondTextureDifficultyTwo.loadFromFile("Assets/tiles_map/backgroundNear_2.png");

	// --- BIOME 3 : difficile ---
	Shared::backboardFirstTextureDifficultyThree.loadFromFile("Assets/tiles_map/backgroundFar_3.png");
	Shared::backboardSecondTextureDifficultyThree.loadFromFile("Assets/tiles_map/backgroundNear_3.png");

	// --- BIOME 4 : extrême ---
	Shared::backboardFirstTextureDifficultyFour.loadFromFile("Assets/tiles_map/backgroundFar_4.png");
	Shared::backboardSecondTextureDifficultyFour.loadFromFile("Assets/tiles_map/backgroundNear_4.png");
}
