#pragma once 

#include "Player.hpp"

class Shop {
public:
	Shop();
	~Shop();

	void render(sf::RenderWindow& window);
	void update();

private:
	sf::RectangleShape shopBackgroundShape, shopCaseOneShape, shopCaseTwoShape, shopCaseThreeShape, shopVictoryShape;
	sf::RectangleShape skinOneShape, skinTwoShape, skinThreeShape;

	sf::Font font;
	sf::Text shop;
};