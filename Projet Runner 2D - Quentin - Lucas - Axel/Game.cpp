#include "Game.hpp"


Game::Game() {}
Game::~Game() {}

void Game::run() {
    sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "My window");
    map.init();

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        map.run();
        render(window);
        window.display();
    }
}

void Game::render(sf::RenderWindow& window) {
    window.clear(sf::Color::Black);
    map.render(window);
}