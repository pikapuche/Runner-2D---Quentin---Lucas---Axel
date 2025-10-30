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
	Game();
	~Game();

	void run();
	void render(sf::RenderWindow& window);
	void restart();

	AssetManager assetManager;
	Shop shop;
	Map map;
	HUD myHud;
	Pause pauseMenu;
	Menu menu;
	EndMenu endMenu;
	WinMenu winMenu;
	SettingsMenu settingsMenu;

	std::shared_ptr<Player> player_ptr;
	sf::Music music;
	sf::Clock clockGame;
	sf::Clock clock;
	sf::Clock menuDelay;
	sf::Clock generateClock;

	int volumeMusic;
	int score;
	int collectible;
	int scoreEnd;
	int speed;
	bool playing;
	bool needClockRestart;
	
	enum GameState {
		Playing,
		MenuStart,
		Pause,
		MenuEndWin,
		MenuEndLose,
		Settings,
		Shop
	};
	
	GameState gameState;
};