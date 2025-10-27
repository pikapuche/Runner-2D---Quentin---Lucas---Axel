#pragma once

#include "AssetManager.hpp"

class Background {
public:
	Background();
	~Background();

	void render(sf::RenderWindow& window);
	void move(float deltatime);
	void startFlashTransition(int newDifficulty);
	
	//getters/setters
	void setBackgroundTexture(int difficulty);

private:
	sf::RectangleShape backboardFirstShape, backboardFirstShape2, backboardSecondShape;
	sf::RectangleShape flashOverlay;

	bool isFlashing = false;
	float flashTimer = 0.f;
	const float flashDuration = 0.3f;
	int currentDifficulty = 1;
};