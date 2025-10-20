#pragma once
#include "Obstacle.hpp"

class Map {
public:
	Map();
	~Map();
	void run();
	void render(sf::RenderWindow& window);
	void init();
	void generate();

	std::vector<Obstacle*> obstacles;
};