#include "Button.hpp"

class WinMenu {
public:
	WinMenu();
	~WinMenu();

	void initMenu();
	void drawMenu(sf::RenderWindow& window, int& score);
	void createStartButton();

	sf::RectangleShape background;
	sf::Text text;
	sf::Font textFont;
	Button backButton;
	Button restartButton;
	sf::Text scoreText;
};

