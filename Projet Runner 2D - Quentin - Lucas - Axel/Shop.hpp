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
	bool getVictoryUnlocked();
	void reset();

private:
	void showMessage(const std::string& message);

	sf::RectangleShape shopBackgroundShape, shopCaseOneShape, shopCaseTwoShape, shopCaseThreeShape, shopVictoryShape;
	sf::RectangleShape skinOneShape, skinTwoShape, skinThreeShape, trophyShape;
	sf::RectangleShape coin1, coin2, coin3, coin4, coin5;
	sf::RectangleShape rect1, rect2, rect3, rect4;
	sf::RectangleShape popupBox;
	sf::Font font;
	sf::Text shopText, shop2Text, skin1Text, skin2Text, skin3Text, victoryText, goldText;
	sf::Text popupText;
	sf::Clock shopClock;
	sf::Clock popupClock, clockRun;
	sf::Vector2i animRun;
	std::string popupMessage;

	float gapX, gapY;
	bool skin1Bool;
	bool skin2Bool;
	bool skin3Bool;
	bool victoryUnlocked;
	bool showPopup;

	const int CHARACTER_ASSET_SIZE = 128;
};