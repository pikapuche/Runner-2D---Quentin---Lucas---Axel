#include "TextureManager.hpp"

TextureLoader::TextureLoader()
{
}

void TextureLoader::loadTextureAssets()
{
	Texture texturePlayer;
	if (!texturePlayer.loadFromFile("../assets/Player1.png")) { std::cout << "File not loaded\n"; }
	else {
		a_textures.push_back(make_shared<Texture>(texturePlayer));
	}
	Texture textureSword;
	if (!textureSword.loadFromFile("../assets/Sword.png")) { std::cout << "File not loaded\n"; }
	else {
		a_textures.push_back(make_shared<Texture>(textureSword));
	}

}
Texture TextureLoader::loadTextureMap(const string& file)
{
	Texture texture;
	if (!texture.loadFromFile(file)) { std::cout << "File not loaded\n"; }

	return texture;
}

void TextureLoader::clearTexture()
{
	m_mapTextures.clear();
}
