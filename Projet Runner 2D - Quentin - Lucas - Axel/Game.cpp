#include "Game.hpp"

Game::Game() {
    if (!music.openFromFile("Assets/Music/MusicInGame.ogg")) std::cout << "caca music" << std::endl << std::endl;
    music.setVolume(static_cast<int>(volumeMusic));
    music.setLooping(true); 
    playing = false;
    map.setScore(score);
    map.setObstacles();
    clockGame.start();
    score = 0;
    collectible = 0;
    gameState = GameState::MenuStart;
}
Game::~Game() {}

void Game::run() {
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "My window", sf::State::Fullscreen) ;
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
    sf::Clock clock;
    float deltaTime = clock.restart().asSeconds();
    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();

        switch (gameState)
        {
        case Game::MenuStart:


            while (const std::optional event = window.pollEvent())
            {
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
                clockGame.start();
                map.setObstacles();
                playing = true;
            }

            score = map.getScore();
            collectible = player_ptr->getPessos();


            // check all the window's events that were triggered since the last iteration of the loop
            while (const std::optional event = window.pollEvent())
            {
                // "close requested" event: we close the window
                if (event->is<sf::Event::Closed>() || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
                    window.close();
            }
            map.run(deltaTime);
            player_ptr->update(deltaTime, map);
            myHud.update(clockGame, score, collectible);

            if (player_ptr->getLife() <= 0) {
                gameState = Game::MenuEndLose;
                playing = false;
                music.stop();
			}

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M))
                gameState = GameState::Shop;
            break;
        case Game::Pause:
            std::cout << "Pause";

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
            break;
        case Game::Settings:
            while (const std::optional event = window.pollEvent())
            {
                // "close requested" event: we close the window
                if (event->is<sf::Event::Closed>() || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
                    window.close();
            }
            break;
        case Game::Shop:
            shop.update();
            std::cout << "Pause";
            break;
        default:
            break;
        }
        render(window);
    }
}

void Game::render(sf::RenderWindow& window) {
    window.clear();
   
    switch (gameState)
    {
    case Game::Playing:
        map.render(window);
        player_ptr->draw(window);
        myHud.drawHUD(window, *player_ptr);
        break;
    case Game::MenuStart:
        menu.drawMenu(window);
        break;
    case Game::Pause:
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