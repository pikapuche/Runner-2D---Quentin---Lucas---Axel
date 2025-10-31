#include "Game.hpp"

Game::Game() {
    Shared::music.setLooping(true);
    Shared::musicMenu.setLooping(true);
    volumeMusic = 20;
    volumeSound = 40;
    Shared::music.setVolume(volumeMusic);
    Shared::musicMenu.setVolume(volumeMusic);
    playing = false;
    needClockRestart = false;

    menuDelay.restart();
    generateClock.restart();

    score = 0;
    collectible = 0;
    speed = 0;
    scoreEnd = 0;
    player_ptr = std::make_shared<Player>();

    gameState = GameState::MenuStart;
}

Game::~Game() {}

void Game::restart() {
    map.reset();
    myHud.initHUD();
    player_ptr->initPlayer(volumeSound);

    score = 0;
    collectible = 0;
    speed = 0;
    volumeMusic = 20;

    playing = true;
    needClockRestart = true;

    Shared::music.stop();
    Shared::music.play();
    clockGame.restart();
    generateClock.restart();
}

void Game::run() {
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "THE PINK PARADOX", sf::State::Fullscreen);
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    float deltaTime;

    while (window.isOpen()) {
        deltaTime = clock.restart().asSeconds();

        while (const std::optional event = window.pollEvent())
            if (event->is<sf::Event::Closed>())
                window.close();

        switch (gameState) {
        case Game::MenuStart:
            while (const std::optional event = window.pollEvent())
                if (event->is<sf::Event::Closed>() || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
                    window.close();
            }

            if (Shared::musicMenu.getStatus() != sf::SoundSource::Status::Playing)
                Shared::musicMenu.play();

            if (menu.playButton.activate()) {
                if (menuDelay.getElapsedTime().asSeconds() > 1.f) {
                    menuDelay.restart();
                    Shared::musicMenu.stop();
                    gameState = Game::Playing;
                }

            if (menu.quitButton.activate())
                window.close();

            if (menu.settingsButton.activate())
                if (menuDelay.getElapsedTime().asSeconds() > 1.f) {
                    menuDelay.restart();
                    gameState = Game::Settings;
                }
            }

            break;
        case Game::Playing:
            if (!playing) {
                player_ptr->initPlayer(volumeSound);
                myHud.initHUD();
                restart();
                //Shared::music.play();
                clockGame.reset();
                playing = true;
            }

            if (Shared::music.getStatus() != sf::SoundSource::Status::Playing)
                Shared::music.play();

            clockGame.start();
            generateClock.start();
            map.run(deltaTime, score, generateClock);
            player_ptr->update(deltaTime, map, collectible, shop);
            scoreEnd = score;
            speed = std::abs(map.getSpeed(score));
            myHud.update(clockGame, score, collectible, speed);

            if (player_ptr->getLife() <= 0) {
                playing = false;
                
                Shared::music.stop();
                gameState = Game::MenuEndLose;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M)) {
                if (menuDelay.getElapsedTime().asSeconds() > 1.f) {
                    menuDelay.restart();
                    gameState = GameState::Shop;
                }
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
            Shared::music.pause();
            player_ptr->stopSounds();
            if (pauseMenu.backButton.activate()) {
                if (menuDelay.getElapsedTime().asSeconds() > 0.5f) {
                    menuDelay.restart();
                    gameState = Game::MenuStart;
                }
            }

            if (pauseMenu.resumeButton.activate() || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
                if (menuDelay.getElapsedTime().asSeconds() > 0.5f) {
                    menuDelay.restart();
                    Shared::music.play();
                    gameState = Game::Playing;
                }
            }
            break;
        case Game::MenuEndWin:
            clockGame.stop();
            player_ptr->stopSounds();
            generateClock.stop();

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
            generateClock.stop();

            player_ptr->stopSounds();

            if (endMenu.backButton.activate()) {
                if (menuDelay.getElapsedTime().asSeconds() > 0.5f) {
                    menuDelay.restart();
                    playing = false;
                    gameState = Game::MenuStart;
                }
            }

            if (endMenu.restartButton.activate()) {
                if (menuDelay.getElapsedTime().asSeconds() > 0.5f) {
                    menuDelay.restart();
                    restart();
                    gameState = Game::Playing;
                }
            }
            break;
        case Game::Settings:
            generateClock.stop();
            settingsMenu.setVolume(volumeSound, volumeMusic);
            if (settingsMenu.backButton.activate() || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
                if (menuDelay.getElapsedTime().asSeconds() > 0.5f) {
                    menuDelay.restart();
                    gameState = Game::MenuStart;
                }
            }
            break;
        case Game::Shop:
            clockGame.stop();
            generateClock.stop();
            shop.update(collectible);
            player_ptr->stopSounds();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
                if (menuDelay.getElapsedTime().asSeconds() > 0.5f) {
                    menuDelay.restart();
                    gameState = GameState::Playing;
                }
            }

            if (shop.getVictoryUnlocked()) {
                gameState = Game::MenuEndWin;
            }
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