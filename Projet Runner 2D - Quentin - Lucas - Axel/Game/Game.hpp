#pragma	once 

#include "../Menu/menu.hpp"
#include "../Menu/HUD.hpp"
#include "../Menu/EndMenu.hpp"
#include "../Menu/Shop.hpp"
#include "../Menu/Pause.hpp"
#include "../Menu/WinMenu.hpp"
#include "../Settings/Settings.hpp"

class Game {
public:
	AssetManager assetManager;
	Shop shop;
	sf::Music music;
	int volumeMusic;
	int score;
	int collectible;
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