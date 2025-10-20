#include "Game.hpp"
#include "menu.hpp"
Game::Game() {}
Game::~Game() {}

void Game::run() {
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "My window");

    Menu menu;
    
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = window.pollEvent())
        {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        window.clear();
        menu.Start(window);
        window.display();
    }
}

void Game::render() {}