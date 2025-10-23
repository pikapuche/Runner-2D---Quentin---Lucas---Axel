#pragma once

#include "Datas.hpp"

class Background {
public:
	sf::RectangleShape backboardFirstShape, backboardFirstShape2, backboardSecondShape;

private:
	sf::Texture backboardFirstTexture, backboardSecondTexture;

public:
	Background();
	~Background();

	void render(sf::RenderWindow& window);
	void move(float deltatime);
	void init();
};