#pragma once 

#include "Player.hpp"

class Shop {
public:
	Shop();
	~Shop();

	void render(sf::RenderWindow& window);
	void update(int& gold);
	void buying(int& gold);

	int getSkin();

private:
	sf::RectangleShape shopBackgroundShape, shopCaseOneShape, shopCaseTwoShape, shopCaseThreeShape, shopVictoryShape;
	sf::RectangleShape skinOneShape, skinTwoShape, skinThreeShape;
	sf::RectangleShape coin1, coin2, coin3, coin4, coin5;
	sf::RectangleShape rect1, rect2, rect3, rect4;

	sf::Font font;
	sf::Text shopText, skin1Text, skin2Text, skin3Text, victoryText, goldText;
	sf::Clock shopClock;

	float gapX, gapY;

	bool skin1Bool = false;
	bool skin2Bool = false;
	bool skin3Bool = false;
	bool victoryUnlocked = false;

	bool showPopup = false;
	sf::Clock popupClock;
	std::string popupMessage;
	sf::RectangleShape popupBox;
	sf::Text popupText;

	void showMessage(const std::string& message);
};