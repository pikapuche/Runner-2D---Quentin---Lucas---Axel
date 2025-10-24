#pragma once

#include "Obstacle.hpp"

class Collectible {
private:

	int sizeX, sizeY;
	float velocity;
	int line = 0;

public:
	Collectible(float _velocity, int _line);
	~Collectible();

	sf::RectangleShape shape;
	void render(sf::RenderWindow& window);
	void move(float deltatime);
	void init();

	int getLine();
	void setPosition(sf::Vector2f pos);
};