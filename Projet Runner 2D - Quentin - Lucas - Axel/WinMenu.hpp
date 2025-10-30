#pragma once

#include "Button.hpp"

class WinMenu {
public:
	WinMenu();
	~WinMenu();

	void initMenu();
	void drawMenu(sf::RenderWindow& window, int score);
	void createStartButton();

	Button backButton;
	Button restartButton;

	sf::RectangleShape background;
	sf::Text text;
	sf::Font textFont;
	sf::Text scoreText;
};

