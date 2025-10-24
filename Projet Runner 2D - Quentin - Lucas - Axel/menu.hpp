#include <iostream>
#include "SFML/Graphics.hpp"
#include "Button.hpp"
using namespace std;
using namespace sf;


class Menu
{
public:
	CircleShape circle;

	Menu();
	~Menu();
	void initMenu();
	void drawMenu(RenderWindow& window);
	void createStartButton();

	RectangleShape background;
	Button playButton;
	Button quitButton;
	Button settingsButton;

};

