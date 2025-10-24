#include "Game.hpp"
#include "menu.hpp"
Game::Game() {}
Game::~Game() {}

void Game::OpenMainMenu() {

    m_uiManager->clearAllUIs();

    auto playButton = m_uiManager->addButton(std::make_shared<Button>(Vector2f{ 275, 450 }, Vector2f{ 200, 150 }, ButtonId::PLAY, 6)).lock();
    auto settingsButton = m_uiManager->addButton(std::make_shared<Button>(Vector2f{ 275, 650 }, Vector2f{ 200, 150 }, ButtonId::SETTINGS, 6)).lock();
    auto quitButton = m_uiManager->addButton(std::make_shared<Button>(Vector2f{ 275, 850 }, Vector2f{ 200, 150 }, ButtonId::QUIT, 6)).lock();


}

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