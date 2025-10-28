#pragma once 

#include "Player.hpp"

class Shop {
public:
	Shop();
	~Shop();

	void render(sf::RenderWindow& window);
	void update(int& gold);
	void buying(int& gold);

private:
	sf::RectangleShape shopBackgroundShape, shopCaseOneShape, shopCaseTwoShape, shopCaseThreeShape, shopVictoryShape;
	sf::RectangleShape skinOneShape, skinTwoShape, skinThreeShape;
	sf::RectangleShape coin1, coin2, coin3, coin4, coin5;
	sf::RectangleShape rect1, rect2, rect3, rect4;
	sf::RectangleShape equipButton1, equipButton2, equipButton3, equipVictoryButton;

	sf::Font font;
	sf::Text shopText, skin1Text, skin2Text, skin3Text, victoryText, goldText;

	float gapX, gapY;
};