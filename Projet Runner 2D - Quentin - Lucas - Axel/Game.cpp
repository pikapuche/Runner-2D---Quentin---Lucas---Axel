#include "Game.hpp"

Game::Game() {
    if (!music.openFromFile("Assets/Music/MusicInGame.ogg")) std::cout << "caca music" << std::endl << std::endl;
    music.setVolume(static_cast<int>(volumeMusic));
    music.setLooping(true);
    playing = false;
    menuDelay.restart();
    generateClock.restart();
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
    
    myHud.initHUD();
    playing = true;

    music.stop();
    music.play();
    clockGame.restart();
    generateClock.restart();

    needClockRestart = true;
}
void Game::run() {
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "THE PINK PARADOX", sf::State::Fullscreen);
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    float deltaTime = clock.restart().asSeconds();
    while (window.isOpen()) {
        deltaTime = clock.restart().asSeconds();

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        switch (gameState) {
        case Game::MenuStart:
            while (const std::optional event = window.pollEvent()) {
                if (event->is<sf::Event::Closed>() || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
                    window.close();
            }
            if (menu.playButton.activate()) {
                if (menuDelay.getElapsedTime().asSeconds() > 1.f) {
                    menuDelay.restart();
                    gameState = Game::Playing;
				}
                
            }

            if (menu.quitButton.activate()) {
                window.close();
            }

            if (menu.settingsButton.activate()) {
                if (menuDelay.getElapsedTime().asSeconds() > 1.f) {
                    menuDelay.restart();
                    gameState = Game::Settings;
                }
            }
            break;
        case Game::Playing:
            if (!playing) {
                player_ptr->initPlayer();
                myHud.initHUD();
                restart();
                music.play();
                clockGame.reset();
                playing = true;
            }
            clockGame.start();
            generateClock.start();
            map.run(deltaTime, score, generateClock);
            player_ptr->update(deltaTime, map, collectible, shop);
            myHud.update(clockGame, score, collectible);
            scoreEnd = score;
            if (player_ptr->getLife() <= 0) {
                playing = false;
                
                music.stop();
                gameState = Game::MenuEndLose;
                
			}

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M))
                if (menuDelay.getElapsedTime().asSeconds() > 1.f) {
                    menuDelay.restart();
                    gameState = GameState::Shop;
                }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
                if (menuDelay.getElapsedTime().asSeconds() > 0.5f) {
                    menuDelay.restart();
                    gameState = Game::Pause;
				}
                
			}
                   
            break;
        case Game::Pause:
            clockGame.stop();
            generateClock.stop();
            if (pauseMenu.backButton.activate()) {
                if (menuDelay.getElapsedTime().asSeconds() > 0.5f) {
                    menuDelay.restart();
                    gameState = Game::MenuStart;
                }
			}
			if (pauseMenu.resumeButton.activate() || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
                if (menuDelay.getElapsedTime().asSeconds() > 0.5f) {
                    menuDelay.restart();
                    gameState = Game::Playing;
                }
			}

            break;
        case Game::MenuEndWin:
            clockGame.stop();

			if (winMenu.backButton.activate()) {
                if (menuDelay.getElapsedTime().asSeconds() > 0.5f) {
                    menuDelay.restart();
                    playing = false;
                    gameState = Game::MenuStart;
                    
                }
                
			}
			if (winMenu.restartButton.activate()) {
                if (menuDelay.getElapsedTime().asSeconds() > 0.5f) {
                    menuDelay.restart();
                    restart();
                    playing = false;
                    gameState = Game::Playing;

                }
			}
            break;
        case Game::MenuEndLose:
            clockGame.stop();
            
            if (endMenu.backButton.activate()) {
                if (menuDelay.getElapsedTime().asSeconds() > 0.5f) {
                    menuDelay.restart();
                    playing = false;
                    gameState = Game::MenuStart;
				}
				
            }
            if (endMenu.restartButton.activate()) {
                if (menuDelay.getElapsedTime().asSeconds() > 0.5f){
                    menuDelay.restart();
                    restart();
                    gameState = Game::Playing;
                }
			}
            break;
        case Game::Settings:
            if (settingsMenu.backButton.activate() || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
                if (menuDelay.getElapsedTime().asSeconds() > 0.5f) {
                    menuDelay.restart();
                    gameState = Game::MenuStart;
                }
                break;
        case Game::Shop:
            clockGame.stop();
            shop.update(collectible);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
                if (menuDelay.getElapsedTime().asSeconds() > 0.5f) {
                    menuDelay.restart();
                    gameState = GameState::Playing;
                }
            }
            if (shop.getVictoryUnlocked())
                gameState = Game::MenuEndWin;
            break;
        default:
            break;
        }

        
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
        map.render(window);
        player_ptr->draw(window);
        myHud.drawHUD(window, *player_ptr);
		pauseMenu.drawMenu(window);
        break;
    case Game::MenuEndWin:
		winMenu.drawMenu(window, scoreEnd);
        break;
    case Game::MenuEndLose:
		endMenu.drawMenu(window, scoreEnd);
        break;
    case Game::Settings:
		settingsMenu.drawMenu(window);
        break;
    case Game::Shop:
        shop.render(window);
        break;
    default:
        break;
    }
    window.display();
}