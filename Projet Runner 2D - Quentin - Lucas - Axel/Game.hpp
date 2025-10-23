#pragma	once 
#include "Map.hpp"
#include "Player.hpp"
#include "menu.hpp"

class Game {
private : 

public:

	shared_ptr<Player> player_ptr = make_shared<Player>();
    Map map;
	Game();
	~Game();
	void run();
	void render(sf::RenderWindow& window);
	int score;
	int collectible;
};