#pragma once
#include "Obstacle.hpp"

class Map {
public:
	Map();
	~Map();
	void run(float deltatime);
	void render(sf::RenderWindow& window);
	void generate();
	void setObstacles();
	void createSeed();

	std::vector<Obstacle*> obstacles;

private:
	int seed = 0;
	std::mt19937 rng;
	int score;
};