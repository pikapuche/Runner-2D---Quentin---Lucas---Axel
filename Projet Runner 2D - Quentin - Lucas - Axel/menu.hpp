#include "Button.hpp"

class Menu {
public:
	Menu();
	~Menu();

	void Start(sf::RenderWindow& window);
	void createStartButton();

	sf::RectangleShape background;
	sf::CircleShape circle;
	//Button playButton;
	//Button quitButton;
	//Button settingsButton;
};

