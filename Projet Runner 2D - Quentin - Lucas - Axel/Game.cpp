#include "Game.hpp"
#include "menu.hpp"
Game::Game() {}
Game::~Game() {}

void Game::run() {


    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "My window");
    window.setFramerateLimit(60);

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


        

        player->update(deltaTime);
        render(window);


        
    }
}

void Game::render(sf::RenderWindow& window) {
    window.clear();
    player->draw(window);
    window.display();
}