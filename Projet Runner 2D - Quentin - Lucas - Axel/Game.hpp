#pragma	once 

#include "Map.hpp"
#include "Shop.hpp"
#include "menu.hpp"
#include "HUD.hpp"

class Game {
public:
	void createStartButton();
	sf::Music music;
	int volumeMusic = 20;
	int score;
	int collectible;
	bool playing;
	Map map;
	HUD myHud;
	std::shared_ptr<Player> player_ptr = std::make_shared<Player>();
	sf::Clock clockGame;
	sf::Clock clock;
	sf::Clock shopDelay;
	Shop shop; 

	enum GameState {
		Playing,
		MenuStart, 
		Pause, 
		MenuEndWin, 
		MenuEndLose, 
		Settings, 
		Shop
	};
	Menu menu;

	Game();
	~Game();

	void run();
	void render(sf::RenderWindow& window);
	GameState gameState;
	AssetManager assetManager;
};