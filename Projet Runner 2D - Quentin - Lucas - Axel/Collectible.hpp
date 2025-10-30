#pragma once

#include "Obstacle.hpp"

class Collectible {
public:
	Collectible(float _velocity, int _line);
	~Collectible();

	void render(sf::RenderWindow& window);
	void move(float deltatime);

	int getLine();
	sf::RectangleShape& getShape();
	void setPosition(sf::Vector2f pos);

private:
	sf::RectangleShape shape;

	float velocity;
	int line;
};