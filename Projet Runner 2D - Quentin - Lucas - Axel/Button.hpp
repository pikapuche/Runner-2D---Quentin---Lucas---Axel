#pragma once
#include "Map.hpp"

class Button {
public:
	Button();
	~Button();

	void activate();
	bool isHovering();

	enum ButtonState {
		NOTHING, PLAY, QUIT, SETTINGS
	};

private:
	//RectangleShape buttonBack;
	//Text buttonText;
	//Font buttonFont;
	//String buttonTextContent;
	//Texture buttonTexture;
};

