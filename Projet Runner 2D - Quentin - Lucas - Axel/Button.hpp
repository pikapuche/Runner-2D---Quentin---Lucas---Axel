#pragma once
#include "Map.hpp"

class Button {
public:
	Button();
	~Button();
	bool activate();
	void drawButton(RenderWindow& window);
	bool isHovering();
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

