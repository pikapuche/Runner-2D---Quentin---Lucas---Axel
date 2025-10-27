#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"

using namespace std;
using namespace sf;

class Button
{
public:
	Button();
	~Button();
	bool activate();
	void drawButton(RenderWindow& window);

	void setState();
	enum ButtonState {
		NOTHING, PLAY, QUIT, SETTINGS
	};

	RectangleShape buttonBack;
	Text buttonText;
	Font buttonFont;
	String buttonTextContent;
	Texture buttonTexture;
	ButtonState buttonState;
};

