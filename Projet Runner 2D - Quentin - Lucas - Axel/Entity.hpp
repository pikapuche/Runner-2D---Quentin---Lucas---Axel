#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"

using namespace std;
using namespace sf;

class Entity {
protected : 

	RectangleShape shape;
	Texture texture;
	Vector2f position;
	Vector2f velocity;
	const float gravity = 150.0f; // Gravité en pixels par seconde carrée (simulation)

public : 

	enum State { NONE, GROUNDED, JUMP };
	State state = NONE;

	Entity(float posX, float posY);
	~Entity() {};

	virtual void collision(Sprite& tile, float deltaTime);
	virtual void draw(RenderWindow& window) = 0;
};