#include "Button.hpp"


Button::Button() : buttonText(buttonFont){
	buttonState = NOTHING;
}
Button::~Button() {

}
bool Button::activate() {
	// R�cup�re la position de la souris (coordonn�es �cran)
	sf::Vector2i mousePos = sf::Mouse::getPosition();
	sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

	// Si le bouton gauche est press� et que la souris est dans le rectangle -> true
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		if (buttonBack.getGlobalBounds().contains(mousePosF)) {
			return true;
		}
	}
	return false;
}


void Button::drawButton(RenderWindow& window) {
	window.draw(buttonBack);
	window.draw(buttonText);

}


bool Button::isHovering() {
	return true;
}