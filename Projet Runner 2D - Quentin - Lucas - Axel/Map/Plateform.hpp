#pragma once

#include "../Map/Obstacle.hpp"

class Plateform {
public:
	Plateform(float _velocity, int _line);
	~Plateform();

	void render(sf::RenderWindow& window);
	void move(float deltatime, int difficulty);
	void init();

	//getters/setters
	int getLine();
	void setPosition(sf::Vector2f pos);

	sf::RectangleShape shape;

private:
	float velocity;
	int line = 0;
};