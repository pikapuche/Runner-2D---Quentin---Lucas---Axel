#include "Game.hpp"

Game::Game() {

    score = 48;
    collectible = 0;
    map.setScore(score);
}
Game::~Game() {}

void Game::run() {
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "My window", sf::State::Fullscreen);
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
    map.generate();
    sf::Clock clock;
    clockGame.start();
    // run the program as long as the window is open
    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();

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
        myHud.update(clockGame);
    }
}

void Game::render(sf::RenderWindow& window) {
    window.clear();
    
    map.render(window);
    player_ptr->draw(window);
    myHud.drawHUD(window);
    window.display();
}