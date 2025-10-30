#include "Collectible.hpp"

Collectible::Collectible(float _velocity, int _line) : line(_line), velocity(_velocity) {
	line = 0;
	shape.setTexture(&Shared::collectibleTexture);
}

Collectible::~Collectible() {}

void Collectible::move(float deltatime) {
	shape.move({ velocity * deltatime, 0 });
}

void Collectible::render(sf::RenderWindow& window) {
	window.draw(shape);
}

int Collectible::getLine() { return line; }
sf::RectangleShape& Collectible::getShape() { return shape; }
void Collectible::setPosition(sf::Vector2f pos) { shape.setPosition(pos); }