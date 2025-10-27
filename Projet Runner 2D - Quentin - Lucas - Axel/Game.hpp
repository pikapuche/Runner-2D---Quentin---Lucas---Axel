#pragma	once 

#include "Map.hpp"
#include "Player.hpp"
#include "menu.hpp"
#include "HUD.hpp"

class Game {
public:
	enum GameState {
		MenuStart, Pause, MenuEndWin, MenuEndLose, Settings, Shop, Play
	};
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
	Menu menu;

	Game();
	~Game();

	void run();
	void render(sf::RenderWindow& window);
	GameState gameState;
	AssetManager assetManager;

	


};