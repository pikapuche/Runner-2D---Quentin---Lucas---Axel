#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"

using namespace std;
using namespace sf;

class Entity {
protected : 

	//Sprite sprite;
	RectangleShape shape;
	Texture texture;
	Vector2f position;
	Vector2f velocity;
	const float gravity = 981.0f;  // Gravit� en pixels par seconde carr�e (simulation)

	Vector2i anim_idle;
	Vector2i anim_jump;

public : 

	enum State { NONE, GROUNDED, JUMP };
	State state = NONE;

	Entity(float posX, float posY);
	~Entity() {};

	virtual void collision(Sprite& tile, float deltaTime);
	virtual void draw(RenderWindow& window) = 0;
};