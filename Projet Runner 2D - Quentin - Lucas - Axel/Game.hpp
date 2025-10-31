#pragma	once 

#include "Map.hpp"
#include "menu.hpp"
#include "HUD.hpp"
#include "EndMenu.hpp"
#include "Shop.hpp"
#include "Pause.hpp"
#include "WinMenu.hpp"
#include "Settings.hpp"

class Game {
public:
	AssetManager assetManager;
	Shop shop;
	int volumeMusic;
	int volumeSound;
	int score;
	int collectible;
	int scoreEnd;
	int speed;
	bool playing;
	bool needClockRestart = false;
	Map map;
	HUD myHud;
	std::shared_ptr<Player> player_ptr = std::make_shared<Player>();
	sf::Clock clockGame;
	sf::Clock clock;
	sf::Clock menuDelay;
	sf::Clock generateClock;
	Pause pauseMenu;
	
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
	EndMenu endMenu;
	WinMenu winMenu;
	SettingsMenu settingsMenu;
	

	Game();
	~Game();

	void run();
	void render(sf::RenderWindow& window);
	void restart();
	GameState gameState;
};