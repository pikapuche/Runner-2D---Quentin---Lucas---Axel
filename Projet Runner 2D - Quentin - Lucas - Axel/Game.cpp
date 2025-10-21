#include "Game.hpp"

Game::Game() {}
Game::~Game() {}

void Game::run() {
    sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "My window");
    window.setFramerateLimit(60);
    map.init();
    sf::Clock clock;

    Time deltaT = clock.restart();

    // run the program as long as the window is open
    while (window.isOpen())
    {
        float deltaTime = deltaT.asSeconds();


        // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = window.pollEvent())
        {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        map.run();

        player->update(deltaTime);
        render(window);

    }
}

void Game::render(sf::RenderWindow& window) {
    window.clear();
    map.render(window);
    //player->draw(window);
    window.display();
}