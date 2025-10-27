#include "Game.hpp"

Game::Game() {
    if (!music.openFromFile("Assets/Music/MusicInGame.ogg")) cout << "caca music" << endl << endl;
    music.setVolume(volumeMusic);
    music.setLooping(true);
    
    score = 1;
    collectible = 0;
    map.setScore(score);
    gameState = MenuStart;
    playing = false;
}
Game::~Game() {}

void Game::run() {
    
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "My window", sf::State::Fullscreen);
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
                if (event->is<sf::Event::Closed>() || Keyboard::isKeyPressed(Keyboard::Key::Escape))
                    window.close();
            }
            if (menu.playButton.activate()) {
                gameState = Game::Play;
                
			}

            if (menu.quitButton.activate()) {
                window.close();
            }

            if (menu.settingsButton.activate()) {
                gameState = Game::Settings;
			}
            render(window);

            break;
        case Game::Play:
            
            if (playing == false) {
                music.play();
                clockGame.start();
                map.generate();
                playing = true;
			}
            
            
                deltaTime = clock.restart().asSeconds();
                score = map.getScore();
                

                // check all the window's events that were triggered since the last iteration of the loop
                while (const std::optional event = window.pollEvent())
                {
                    // "close requested" event: we close the window
                    if (event->is<sf::Event::Closed>() || Keyboard::isKeyPressed(Keyboard::Key::Escape))
                        window.close();
                }
                map.run(deltaTime);
                player_ptr->update(deltaTime, map);
                render(window);
                myHud.update(clockGame, score);
            break;
        case Game::Pause:
            cout << "Pause";
            
            break;
        case Game::MenuEndWin:
            cout << "Pause";
            break;
        case Game::MenuEndLose:
            cout << "Pause";
            break;
        case Game::Settings:
            cout << "Pause";
            break;
        case Game::Shop:
            cout << "Pause";
            break;
        default:
            break;
        }
    
    }

    
    
    
    
}

void Game::render(sf::RenderWindow& window) {
    window.clear();
    
    
    switch (gameState)
    {
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
        break;
    case Game::Play:
        map.render(window);
        player_ptr->draw(window);
        myHud.drawHUD(window);
        break;
    default:
        break;
    }
    window.display();

}