#pragma	once 
#include "Map.hpp"
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Player.hpp"
#include "menu.hpp"
#include "HUD.hpp"
class Game {
private : 

public:
	enum GameState {
		MenuStart, Pause, MenuEndWin, MenuEndLose, Settings, Shop
	};
	shared_ptr<Player> player_ptr = make_shared<Player>();
    Map map;
	HUD myHud;
	Clock clockGame;
	Game();
	~Game();
	void run();
	void render(sf::RenderWindow& window);
};