#include <iostream>
#include "SFML/Graphics.hpp"

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

private:

};

