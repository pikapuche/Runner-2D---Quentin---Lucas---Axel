#include "Button.hpp"


Button::Button() : buttonText(buttonFont), spriteButton(buttonTexture){
	buttonState = NOTHING;
	normalColor = buttonBack.getFillColor();
	hoverColor = sf::Color(200, 200, 200);
	hoverable = true;
	hovered = false;
	buttonBack.setFillColor(normalColor);
}
Button::~Button() {

}
bool Button::activate() {
	sf::Vector2i mousePos = sf::Mouse::getPosition();
	sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		if (buttonBack.getGlobalBounds().contains(mousePosF)) {
			return true;
		}
	}
	return false;
}


void Button::drawButton(sf::RenderWindow& window) {
	window.draw(buttonBack);
	window.draw(buttonText);

}


bool Button::isHovering() {
	sf::Vector2i mousePos = sf::Mouse::getPosition();
	sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

	bool over = buttonBack.getGlobalBounds().contains(mousePosF);
	if (!hoverable) {
		if (hovered) {
			hovered = false;
			hover(false);
		}
		return false;
	}

	if (over != hovered) {
		hovered = over;
		hover(over);
	}
	return over;
}
void Button::setHoverable(bool enabled) {
	hoverable = enabled;
	if (!hoverable) {
		hovered = false;
		hover(false);
	}
}

void Button::setHoverColors(const sf::Color& normal, const sf::Color& hover) {
	normalColor = normal;
	hoverColor = hover;
	this->hover(hovered);
}

void Button::hover(bool enable) {
	if (enable && hoverable) {
		buttonBack.setFillColor(hoverColor);
		buttonText.setFillColor(sf::Color::Black);
	}
	else {
		buttonBack.setFillColor(normalColor);
		buttonText.setFillColor(sf::Color::White);
	}
}