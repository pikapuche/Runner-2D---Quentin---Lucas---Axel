#pragma once

#include "Datas.hpp"

// Classe responsable du chargement des textures, sons et autres ressources SFML
class AssetManager {
public:
    AssetManager();
    ~AssetManager() = default;

private:
    void loadAssetsFromFiles();
};
