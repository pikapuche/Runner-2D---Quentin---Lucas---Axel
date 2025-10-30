#pragma once

#include "Button.hpp"

class EndMenu {
public:
	EndMenu();
	~EndMenu();

	void initMenu();
	void drawMenu(sf::RenderWindow& window, int score);
	void createStartButton();

	int scoreEnd;

	sf::RectangleShape background;
	sf::Text text;
	sf::Text scoreText;
	sf::Font textFont;

	Button backButton;
	Button restartButton;
};

