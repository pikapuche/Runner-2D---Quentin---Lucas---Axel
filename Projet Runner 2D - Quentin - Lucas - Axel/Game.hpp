#pragma	once 
#include "Map.hpp"
#include <iostream>
class Game {

public:
	Game();
	~Game();
	void run();
	void render(sf::RenderWindow& window);

	Map map;
};