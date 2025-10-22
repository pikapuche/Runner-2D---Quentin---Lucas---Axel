#pragma once

#include "Obstacle.hpp"

class Plateform {
private:

	int sizeX, sizeY;
	float velocity;
	int line = 0;
	sf::Texture shapeTexture;

public:
	Plateform(float _velocity, int _line);
	~Plateform();

	sf::RectangleShape shape;
	void render(sf::RenderWindow& window);
	void move(float deltatime);
	void init();

	int getLine();
	void setPosition(sf::Vector2f pos);
};