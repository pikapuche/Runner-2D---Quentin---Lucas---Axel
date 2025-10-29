#include "Game.hpp"

Game::Game() {
    if (!music.openFromFile("Assets/Music/MusicInGame.ogg")) std::cout << "caca music" << std::endl << std::endl;
    music.setVolume(static_cast<int>(volumeMusic));
    music.setLooping(true);
    playing = false;
    map.setScore(score);
    shopDelay.restart();
    score = 0;
    collectible = 0;
    volumeMusic = 20;
    gameState = GameState::MenuStart;
}
Game::~Game() {}

void Game::restart() {
    map.reset();
    player_ptr->initPlayer();
    score = 0;
    collectible = 0;
    volumeMusic = 20;
    
    map.setScore(score);
    myHud.initHUD();
    playing = true;

    music.stop();
    music.play();
    clockGame.restart();

    needClockRestart = true;
}
void Game::run() {
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "My window", sf::State::Fullscreen);
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
    sf::Clock clock;
    float deltaTime = clock.restart().asSeconds();
    while (window.isOpen()) {
        deltaTime = clock.restart().asSeconds();

        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>() || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
                window.close();
        }

        switch (gameState) {
        case Game::MenuStart:
            while (const std::optional event = window.pollEvent()) {
                if (event->is<sf::Event::Closed>() || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
                    window.close();
            }
            if (menu.playButton.activate()) {
                gameState = Game::Playing;
            }

            if (menu.quitButton.activate()) {
                window.close();
            }

            if (menu.settingsButton.activate()) {
                gameState = Game::Settings;
            }
            break;
        case Game::Playing:
            if (!playing) {
                player_ptr->initPlayer();
                myHud.initHUD();
                music.play();
                playing = true;
                clockGame.reset();
            }
            clockGame.start();
            score = map.getScore();
            map.run(deltaTime);
            player_ptr->update(deltaTime, map, collectible, shop);
            myHud.update(clockGame, score, collectible);

            if (player_ptr->getLife() <= 0) {
                gameState = Game::MenuEndLose;
                playing = false;
                music.stop();
			}

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M))
                if (shopDelay.getElapsedTime().asSeconds() > 1.f) {
                    shopDelay.restart();
                    gameState = GameState::Shop;
                }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P)) {
                gameState = Game::Pause;
			}
                   
            break;
        case Game::Pause:
            clockGame.stop();
            if (pauseMenu.backButton.activate()) {
                playing = false;
				gameState = Game::MenuStart;
			}
			if (pauseMenu.resumeButton.activate()) {
				gameState = Game::Playing;
			}

            break;
        case Game::MenuEndWin:
            std::cout << "Pause";
            break;
        case Game::MenuEndLose:
            while (const std::optional event = window.pollEvent())
            {
                if (event->is<sf::Event::Closed>() || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
                    window.close();
            }
            if (endMenu.backButton.activate()) {
				gameState = Game::MenuStart;
            }
			if (endMenu.restartButton.activate()) {
				restart();
				gameState = Game::Playing;
			}
            break;
        case Game::Settings:
            break;
        case Game::Shop:
            clockGame.stop();
            shop.update(collectible);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M))
                if (shopDelay.getElapsedTime().asSeconds() > 1.f) {
                    shopDelay.restart();
                    gameState = GameState::Playing;
                }
            break;
        default:
            break;
        }
        if (shop.getVictoryUnlocked())
            gameState = Game::MenuEndWin;
        render(window);
    }
}

void Game::render(sf::RenderWindow& window) {
    window.clear();

    switch (gameState) {
    case Game::Playing:
        map.render(window);
        player_ptr->draw(window);
        myHud.drawHUD(window, *player_ptr);
        break;
    case Game::MenuStart:
        menu.drawMenu(window);
        break;
    case Game::Pause:
		pauseMenu.drawMenu(window);
        break;
    case Game::MenuEndWin:
        break;
    case Game::MenuEndLose:
		endMenu.drawMenu(window);
        break;
    case Game::Settings:
        break;
    case Game::Shop:
        shop.render(window);
        break;
    default:
        break;
    }
    window.display();
}