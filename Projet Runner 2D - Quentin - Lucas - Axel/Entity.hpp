#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

using namespace std;
using namespace sf;

class Entity {
protected : 



	Entity();
	~Entity();

	virtual void collision(Sprite& tile, float deltaTime);
	virtual void draw(RenderWindow& window) = 0;
};