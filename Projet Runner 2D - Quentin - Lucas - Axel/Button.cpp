#include "Button.hpp"

Button::Button() : buttonText(buttonFont){
	buttonState = NOTHING;
	
}
Button::~Button() {

}
bool Button::activate() {
	// Récupère la position de la souris (coordonnées écran)
	sf::Vector2i mousePos = sf::Mouse::getPosition();
	sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

	// Si le bouton gauche est pressé et que la souris est dans le rectangle -> true
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

void Button::setState() {

}