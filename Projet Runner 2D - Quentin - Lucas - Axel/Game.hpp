#pragma	once 
#include "Map.hpp"
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Player.hpp"
#include "menu.hpp"

class Game {
private : 

public:

	shared_ptr<Player> player = make_shared<Player>(100, 100);
  Map map;
	Game();
	~Game();
	void run();
	void render(sf::RenderWindow& window);
};