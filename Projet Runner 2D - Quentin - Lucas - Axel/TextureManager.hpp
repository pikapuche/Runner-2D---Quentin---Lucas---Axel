#pragma once
#include "SFML/Graphics.hpp"

#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;
using namespace sf;

class TextureLoader {
public:

    TextureLoader();

    void loadTextureAssets();
    Texture loadTextureMap(const string& file);
    
    string getLayerTexture(char tile);
    
    void clearTexture();

private:

    unordered_map <string, shared_ptr<Texture>> m_mapTextures;
    vector<shared_ptr<Texture>> a_textures;
};