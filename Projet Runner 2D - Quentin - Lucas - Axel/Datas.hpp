#include <iostream>
#include <SFML/Graphics.hpp>
#include "SFML/Audio.hpp"
#include <random>
#include <algorithm>
#include <cmath>

namespace STGS {
    static const int WIDTH = sf::VideoMode::getDesktopMode().size.x;
    static const int HEIGHT = sf::VideoMode::getDesktopMode().size.y;
    static const int GAP_X = 120;
    static const int GAP_Y = 60;
}

class Shared {
public:
    static sf::Texture tileSetTexture;
    static sf::Texture collectibleTexture;
    static sf::Texture backboardFirstTextureDifficultyOne;
    static sf::Texture backboardSecondTextureDifficultyOne;
    static sf::Texture backboardFirstTextureDifficultyTwo;
    static sf::Texture backboardSecondTextureDifficultyTwo;
    static sf::Texture backboardFirstTextureDifficultyThree;
    static sf::Texture backboardSecondTextureDifficultyThree; 
    static sf::Texture backboardFirstTextureDifficultyFour;
    static sf::Texture backboardSecondTextureDifficultyFour;
    static sf::Texture goldTexture;
    static sf::Texture heart1Texture;
    static sf::Texture heart2Texture;
    static sf::Texture heart3Texture;
    static sf::Texture groundTexture;
    static sf::Texture trophyTexture;
    static sf::Texture cadre1;
    static sf::Texture playerTexture;
    static sf::Texture playerJumpTexture;
    static sf::Texture playerJetpackTexture;
    static sf::Texture playerSlideTexture;
    static sf::Texture backgroundMenu;
    static sf::Texture winBackgroundMenu;
    static sf::Texture loseBackgroundMenu;

    static sf::SoundBuffer bufferRunGravel, bufferRun, bufferJump, bufferJetpack, bufferCoin, bufferHurt, bufferSlide, bufferJohn;
};