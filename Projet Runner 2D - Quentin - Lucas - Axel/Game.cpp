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
            render(window);

            break;
        case Game::Playing:
            
            if (playing == false) {
                player_ptr->shape.setPosition({ 100.f, 100.f });
                music.play();
                clockGame.start();
                map.setObstacles();
                playing = true;
			}
            
            
                deltaTime = clock.restart().asSeconds();
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
                render(window);
                myHud.update(clockGame, score, collectible);
            break;
        case Game::Pause:
            std::cout << "Pause";
            
            break;
        case Game::MenuEndWin:
            std::cout << "Pause";
            break;
        case Game::MenuEndLose:
            std::cout << "Pause";
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
            std::cout << "Pause";
            break;
        default:
            break;
        }
        switch (gameState)
        {
        case Game::Playing:
            map.run(deltaTime);
            score = map.getScore();
            player_ptr->update(deltaTime, map);
            myHud.update(clockGame, score, collectible);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M))
                gameState = GameState::Shop;
            break;
        case Game::MenuStart:
            break;
        case Game::Pause:
            break;
        case Game::MenuEndWin:
            break;
        case Game::MenuEndLose:
            break;
        case Game::Settings:
            break;
        case Game::Shop:
            shop.update();
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