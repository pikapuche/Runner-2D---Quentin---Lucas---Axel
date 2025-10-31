#pragma once

#include "Button.hpp"

class Menu {
public:
	Menu();
	~Menu();

	void initMenu();
	void drawMenu(sf::RenderWindow& window);

	Button playButton;
	Button quitButton;
	Button settingsButton;

	sf::RectangleShape background;
	sf::CircleShape circle;
	sf::Text gameTitle;
	sf::Font font;
};

