#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>
#include <algorithm>

namespace STGS {
    static const int WIDTH = sf::VideoMode::getDesktopMode().size.x;
    static const int HEIGHT = sf::VideoMode::getDesktopMode().size.y;
    static const int GAP_Y = 60;
}