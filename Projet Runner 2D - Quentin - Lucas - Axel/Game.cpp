#include "Game.hpp"

Game::Game() {
    if (!music.openFromFile("Assets/Music/MusicInGame.ogg")) cout << "caca music" << endl << endl;
    music.setVolume(volumeMusic);
    music.setLooping(true);
    music.play();
    score = 1;
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

    while (window.isOpen())
    {
        score = map.getScore();
        float deltaTime = clock.restart().asSeconds();

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>() || Keyboard::isKeyPressed(Keyboard::Key::Escape))
                window.close();
        }
        map.run(deltaTime);
        score = map.getScore();
        player_ptr->update(deltaTime, map);
        render(window);
        myHud.update(clockGame, score);
    }
}

void Game::render(sf::RenderWindow& window) {
    window.clear();
    
    map.render(window);
    player_ptr->draw(window);
    myHud.drawHUD(window, *player_ptr);
    window.display();
}