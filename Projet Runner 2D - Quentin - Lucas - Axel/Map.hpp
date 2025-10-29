#pragma once

#include "Obstacle.hpp"
#include "Plateform.hpp"
#include "Collectible.hpp"

class Map {
public:
	Map();
	~Map();

	void run(float deltatime, int& score);
	void render(sf::RenderWindow& window);
	void removeObstacle(Obstacle* obs);
	void removeCollectible(Collectible* col);
	void reset();
	//getters/setters
	sf::FloatRect getBounds();
	sf::FloatRect getBounds2();
	std::vector<Plateform*> getPlatformVector();
	std::vector<Obstacle*> getVectObs();
	std::vector<Collectible*> getCollectible();
	std::vector<Plateform*> getPlateform();
	sf::RectangleShape getGround();
	sf::RectangleShape getGround2();
	int getDifficulty();
	void setScore(int score);
	void setObstacles();
	void incrementScore(int& score);
		

private:
	void createSeed();
	void makeGround();
	void moveGround(float deltaTime);

	std::vector<Obstacle*> obstacles;
	std::vector<Plateform*> plateforms;
	std::vector<Collectible*> collectibles;
	std::mt19937 rng;
	sf::RectangleShape ground, ground2;
	sf::Clock generateClock;

	Background bg;

	int _score;
	int seed = 0;
	float delay;
	int difficulty;
};