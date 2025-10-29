#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"
#include "Player.hpp"
#include "Map.hpp"

class HUD {
public:
	HUD();
	~HUD();

	void initHUD();
	void drawHUD(sf::RenderWindow& window, Player& player);
	void update(sf::Clock& clock, int& score, int& pessos);

private:

	int sbstr;
	float seconds;
	sf::Time elapsed;

	sf::Text timer;
	sf::Text score;
	sf::Text gold;
	sf::Font font;
	sf::RectangleShape heart1;
	sf::RectangleShape heart2;
	sf::RectangleShape heart3;
	sf::RectangleShape goldPiece;
};