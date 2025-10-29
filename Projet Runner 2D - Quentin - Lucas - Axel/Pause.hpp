#include "Button.hpp"

class Pause {
public:
	Pause();
	~Pause();

	void initMenu();
	void drawMenu(sf::RenderWindow& window);
	void createStartButton();

	sf::RectangleShape background;
	sf::Text text;
	sf::Font textFont;
	Button backButton;
	Button resumeButton;
	Button epilepticButton;
};

