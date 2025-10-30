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
	void update(sf::Clock& clock, int score, int pessos, float speed);

private:
	sf::Time elapsed;
	sf::Text timerText;
	sf::Text scoreText;
	sf::Text goldText;
	sf::Text speedText;
	sf::Font font;
	sf::RectangleShape heart1Shape;
	sf::RectangleShape heart2Shape;
	sf::RectangleShape heart3Shape;
	sf::RectangleShape goldPieceShape;

	int sbstr, sbstrSpeed;
	float seconds;
};