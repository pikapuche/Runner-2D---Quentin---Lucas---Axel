#pragma	once 

#include "Map.hpp"
#include "Player.hpp"
#include "menu.hpp"
#include "HUD.hpp"

class Game {
public:
	Game();
	~Game();

	void run();
	void render(sf::RenderWindow& window);

	int score;
	int collectible;
	int volumeMusic = 10;

	AssetManager assetManager;
    Map map;
	std::shared_ptr<Player> player_ptr = std::make_shared<Player>();
	HUD myHud;
	sf::Clock clockGame;
	sf::Clock clock;
	sf::Music music;

	enum GameState {
		MenuStart, Pause, MenuEndWin, MenuEndLose, Settings, Shop
	};
};