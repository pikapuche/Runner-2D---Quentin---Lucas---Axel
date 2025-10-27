#include <iostream>
#include <SFML/Graphics.hpp>
#include "SFML/Audio.hpp"
#include <random>
#include <algorithm>

namespace STGS {
    static const int WIDTH = sf::VideoMode::getDesktopMode().size.x;
    static const int HEIGHT = sf::VideoMode::getDesktopMode().size.y;
    static const int GAP_Y = 60;
}

class Shared {
public:
    static sf::Texture tileSetTexture;
    static sf::Texture collectibleTexture;
    static sf::Texture backboardFirstTextureDifficultyOne, backboardSecondTextureDifficultyOne;
    static sf::Texture backboardFirstTextureDifficultyTwo, backboardSecondTextureDifficultyTwo;
    static sf::Texture backboardFirstTextureDifficultyThree, backboardSecondTextureDifficultyThree;
    static sf::Texture backboardFirstTextureDifficultyFour, backboardSecondTextureDifficultyFour;
    static sf::Texture goldTexture, heart1Texture, heart2Texture, heart3Texture;
    static sf::Texture groundTexture;
    static sf::Texture playerTexture, playerJumpTexture, playerJetpackTexture;
};