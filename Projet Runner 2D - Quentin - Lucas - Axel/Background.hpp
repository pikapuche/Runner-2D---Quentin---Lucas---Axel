#pragma once

#include "AssetManager.hpp"

class Background {
private:
	sf::RectangleShape backboardFirstShape, backboardFirstShape2, backboardSecondShape;
	sf::RectangleShape flashOverlay;

	bool isFlashing = false;
	float flashTimer = 0.f;
	const float flashDuration = 0.3f;
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