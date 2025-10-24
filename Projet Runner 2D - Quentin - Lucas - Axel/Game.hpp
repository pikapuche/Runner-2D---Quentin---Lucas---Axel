#pragma	once 
#include <iostream>
#include "SFML/Graphics.hpp"
<<<<<<< Updated upstream
=======
#include "Player.hpp"
#include "menu.hpp"
#include "UiManager.hpp"

>>>>>>> Stashed changes
class Game {

public:
	Game();
	~Game();
	void run();
<<<<<<< Updated upstream
	void render();
=======
	void render(sf::RenderWindow& window);

	void OpenMainMenu();

	enum GameState {
		MAINMENU, PAUSE, PLAY, SETTINGS, CREDITS
	};

	std::shared_ptr<UiManager>		m_uiManager;
>>>>>>> Stashed changes
};