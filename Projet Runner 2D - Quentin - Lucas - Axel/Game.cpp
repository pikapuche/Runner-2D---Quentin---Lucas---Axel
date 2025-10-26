#include "Game.hpp"

Game::Game() {
    if (!music.openFromFile("Assets/Music/MusicInGame.ogg")) std::cout << "caca music" << std::endl << std::endl;
    music.setVolume(static_cast<int>(volumeMusic));
    music.setLooping(true);
    music.play();
    map.setScore(score);
    map.setObstacles();
    clockGame.start();
    score = 0;
    collectible = 0;
}
Game::~Game() {}

void Game::run() {
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "My window", sf::State::Fullscreen);
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    while (window.isOpen()) {
        score = map.getScore();
        collectible = player_ptr->getPessos();
        float deltaTime = clock.restart().asSeconds();

        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>() || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
                window.close();
        }
        map.run(deltaTime);
        score = map.getScore();
        player_ptr->update(deltaTime, map);
        myHud.update(clockGame, score, collectible);
        render(window);
    }
}

void Game::render(sf::RenderWindow& window) {
    window.clear();
    
    map.render(window);
    player_ptr->draw(window);
    myHud.drawHUD(window, *player_ptr);

    window.display();
}