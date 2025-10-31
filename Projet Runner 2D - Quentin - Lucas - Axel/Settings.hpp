#pragma once
#include "Button.hpp"

class SettingsMenu {
public:
	SettingsMenu();
	~SettingsMenu();

	void initMenu();
	void setVolume(int& volumeSound, int& volumeMusic);
	void updateSettings();
	void drawMenu(sf::RenderWindow& window);

	sf::RectangleShape background;
	sf::Text text;
	sf::Font textFont;
	Button backButton;
	Button restartButton;
	Button soundPlusButton;
	Button soundMinusButton;

	// volume

	sf::RectangleShape upMusicShape, downMusicShape, upSoundShape, downSoundShape;
	sf::Text volumeTextMusic;
	sf::Text volumeTextSoundEffects;
	sf::Clock clickClock;

	float clickDelay;

	sf::Vector2i mousePos;
	sf::Vector2f mousePosF;
};

