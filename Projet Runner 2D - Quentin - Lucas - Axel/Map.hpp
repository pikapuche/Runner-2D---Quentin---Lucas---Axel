#pragma once
#include "Obstacle.hpp"
#include "Plateform.hpp"
#include "Collectible.hpp"

class Map {
public:
	Map();
	~Map();
	void run(float deltatime);
	void render(sf::RenderWindow& window);
	void generate();

	//getters/setters
	sf::FloatRect getBounds();
	int getScore();
	int getDifficulty();
	std::vector<Obstacle*> getVectObs();
	sf::RectangleShape getGround();
	sf::RectangleShape getGround2();


private:
	std::vector<Obstacle*> obstacles;
	std::vector<Plateform*> plateforms;
	std::vector<Collectible*> collectibles;
	int seed = 0;
	std::mt19937 rng;
	int score;
	sf::RectangleShape ground, ground2;
	Background bg;

	void setObstacles();
	void createSeed();
	void makeGround();
	void moveGround(float deltaTime);
	sf::Texture groundTexture;

	sf::Clock generateClock;
	float delay;
	int difficulty;
};