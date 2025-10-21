#pragma once

#include "Datas.hpp"

class Obstacle {
private:

	int sizeX, sizeY;
	float velocity;
	int line = 0; 

public:
	Obstacle(float _velocity, int _line);
	~Obstacle();

	sf::RectangleShape shape;
	void render(sf::RenderWindow& window);
	void move(float deltatime);
	void init();

	int getLine();
	void setPosition(sf::Vector2f pos);
};