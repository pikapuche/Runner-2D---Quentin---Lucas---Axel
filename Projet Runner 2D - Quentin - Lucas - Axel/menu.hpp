
#include "Button.hpp"

using namespace std;
using namespace sf;


class Menu
{
public:
	CircleShape circle;

	Menu();
	~Menu();
	void Start(RenderWindow& window);
	void createStartButton();

	RectangleShape background;
	//Button playButton;
	//Button quitButton;
	//Button settingsButton;

};

