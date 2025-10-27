#pragma once
#include "Map.hpp"

class Button {
public:
	Button();
	~Button();
	bool activate();
	void drawButton(sf::RenderWindow& window);
	bool isHovering();
	enum ButtonState {
		NOTHING, PLAY, QUIT, SETTINGS, BACK, RESTART
	};


	sf::RectangleShape buttonBack;
	sf::Text buttonText;
	sf::Font buttonFont;
	sf::String buttonTextContent;
	sf::Texture buttonTexture;
	ButtonState buttonState;
};

