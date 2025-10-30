#pragma once

#include "Button.hpp"

class SettingsMenu {
public:
	SettingsMenu();
	~SettingsMenu();

	void initMenu();
	void drawMenu(sf::RenderWindow& window);
	void createStartButton();

	Button backButton;
	Button restartButton;
	Button soundPlusButton;
	Button soundMinusButton;

	sf::RectangleShape background;
	sf::Text text;
	sf::Font textFont;
};

