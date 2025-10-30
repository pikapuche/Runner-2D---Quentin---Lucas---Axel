#pragma once

#include "AssetManager.hpp"

class Background {
public:
	Background();
	~Background();

	void render(sf::RenderWindow& window);
	void move(float deltatime, int difficulty);
	void startFlashTransition(int newDifficulty);
	
	//getters/setters
	void setBackgroundTexture(int difficulty);
	void setCurrentDifficulty(int difficulty);

private:
	sf::RectangleShape backboardFirstShape; 
	sf::RectangleShape backboardFirstShape2;
	sf::RectangleShape backboardSecondShape;
	sf::RectangleShape flashOverlay;

	bool isFlashing;
	float flashTimer;
	int currentDifficulty;

	float speedFar;
	float speedNear;
	float flashDuration;
};