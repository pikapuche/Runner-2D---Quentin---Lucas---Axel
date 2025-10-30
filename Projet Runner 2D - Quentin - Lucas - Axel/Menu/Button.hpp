#pragma once
#include "../Settings/Datas.hpp"

class Button {
public:
	Button();
	~Button();
	bool activate();
	void drawButton(sf::RenderWindow& window);
	bool isHovering();
	void setHoverable(bool enabled);
	void setHoverColors(const sf::Color& normal, const sf::Color& hover);
	void hover(bool enable);
	bool hoverable = true;
	bool hovered = false;
	sf::Color normalColor = sf::Color::White;
	sf::Color hoverColor = sf::Color(200, 200, 200);
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

