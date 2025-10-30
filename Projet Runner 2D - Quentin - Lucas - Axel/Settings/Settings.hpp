#pragma once

#include "../Menu/Button.hpp"

class SettingsMenu {
public:
	SettingsMenu();
	~SettingsMenu();

	void initMenu();
	void drawMenu(sf::RenderWindow& window);
	void createStartButton();
	void updateSettings();

	sf::RectangleShape background;
	sf::Text text;
	sf::Font textFont;
	Button backButton;
	Button restartButton;
};

