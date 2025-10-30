#pragma once

#include "Map.hpp"

class Button {
public:
	Button();
	~Button();

	void drawButton(sf::RenderWindow& window);
	void hover(bool enable);

	bool activate();
	bool isHovering();
	void setHoverable(bool enabled);
	void setHoverColors(const sf::Color& normal, const sf::Color& hover);

	sf::Color normalColor;
	sf::Color hoverColor;

	bool hoverable;
	bool hovered;

	enum ButtonState {
		NOTHING, PLAY, QUIT, SETTINGS, BACK, RESTART, RESUME
	};

	sf::RectangleShape buttonBack;
	sf::Text buttonText;
	sf::Font buttonFont;
	sf::Sprite spriteButton;
	sf::String buttonTextContent;
	sf::Texture buttonTexture;

	ButtonState buttonState;
};

