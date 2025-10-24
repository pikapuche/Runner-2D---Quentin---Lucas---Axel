#include "Button.hpp"

Button::Button() : buttonText(buttonFont){
	buttonState = NOTHING;
	
}
Button::~Button() {

}
void Button::activate() {
	switch (buttonState)
	{
	case Button::NOTHING:
		break;
	case Button::PLAY:
		break;
	case Button::QUIT:
		break;
	case Button::SETTINGS:
		break;
	default:
		break;
	}
}

bool Button::isHovering() {

}
void Button::drawButton(RenderWindow& window) {
	window.draw(buttonBack);
	window.draw(buttonText);

}

void Button::setState() {

}