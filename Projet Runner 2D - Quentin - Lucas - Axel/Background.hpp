#pragma once

#include "Datas.hpp"

class Background {
private:
	sf::RectangleShape backboardFirstShape, backboardFirstShape2, backboardSecondShape;
	sf::Texture backboardFirstTextureDifficultyOne, backboardSecondTextureDifficultyOne;
	sf::Texture backboardFirstTextureDifficultyTwo, backboardSecondTextureDifficultyTwo;
	sf::Texture backboardFirstTextureDifficultyThree, backboardSecondTextureDifficultyThree;
	sf::Texture backboardFirstTextureDifficultyFour, backboardSecondTextureDifficultyFour;
	sf::Texture transitionTextureOneTwo, transitionTextureTwoThree, transitionTextureThreeFour;

	bool isFlashing = false;
	float flashTimer = 0.f;
	const float flashDuration = 0.3f;
	sf::RectangleShape flashOverlay;
	int currentDifficulty = 1;
public:
	Background();
	~Background();

	void render(sf::RenderWindow& window);
	void move(float deltatime);
	void init();
	void setBackgroundTexture(int difficulty);
	void startFlashTransition(int newDifficulty);
};