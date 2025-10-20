#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"

using namespace std;
using namespace sf;

class Entity {
protected : 

	Sprite sprite;
	Texture texture;
	Vector2f position;
	Vector2f velocity;
	const float gravity = 981.0f;  // Gravité en pixels par seconde carrée (simulation)

	Vector2i anim_idle;
	Vector2i anim_jump;

public : 

	enum State { NONE, GROUNDED, JUMP };
	State state = NONE;

	Entity(float posX, float posY);

	virtual void collision(Sprite& tile, float deltaTime);
	virtual void draw(RenderWindow& window) = 0;

	Sprite& getSprite();

};