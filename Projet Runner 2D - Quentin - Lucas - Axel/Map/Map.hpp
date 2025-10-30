#pragma once

#include "../Map/Obstacle.hpp"
#include "../Map/Plateform.hpp"
#include "../Map/Collectible.hpp"

class Map {
public:
	Map();
	~Map();

	void run(float deltatime, int& score, sf::Clock& generateClock);
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
	void setObstacles(int& score);
	void incrementScore(int& score);
	float getSpeed(int score);

private:
	void createSeed();
	void makeGround();
	void moveGround(float deltaTime);

	std::vector<Obstacle*> obstacles;
	std::vector<Plateform*> plateforms;
	std::vector<Collectible*> collectibles;
	std::mt19937 rng;
	sf::RectangleShape ground, ground2;

	Background bg;

	int seed = 0;
	float delay;
	int difficulty;
};