#pragma	once 
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Player.hpp"

class Game {
private : 

public:

	shared_ptr<Player> player = make_shared<Player>(100, 100);

	Game();
	~Game();
	void run();
	void render(sf::RenderWindow& window);
};