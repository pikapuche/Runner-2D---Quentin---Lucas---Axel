#pragma once 

#include "Player.hpp"

class Shop {
public:
	Shop();
	~Shop();

	void render(sf::RenderWindow& window);
	void update();

private:
	sf::RectangleShape shopBackgroundShape, shopCaseShape;
};