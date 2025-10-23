#pragma once

#include "Datas.hpp"

class Obstacle {
private:

	int sizeX, sizeY;
	float velocity;
	int line = 0; 
	sf::Texture shapeTexture;

public:
	Obstacle(float _velocity, int _line);
	~Obstacle();

	sf::RectangleShape shape, safePlaceShape;
	void render(sf::RenderWindow& window);
	void move(float deltatime);
	void init();

	int getLine();
	sf::FloatRect getSafePlaceBounds();
	void setPosition(sf::Vector2f pos);
};