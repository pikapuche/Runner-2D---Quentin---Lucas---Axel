#include "Obstacle.hpp"

Obstacle::Obstacle(float _velocity, int _line) : line(_line), velocity(_velocity) {
}

Obstacle::~Obstacle() {
}

void Obstacle::init() {
	sizeX = STGS::WIDTH / 3;
	sizeY = STGS::HEIGHT / 5;
	shape.setFillColor(sf::Color::Red);
	shape.setSize({ STGS::WIDTH / 5, STGS::HEIGHT / 3 - STGS::GAP_Y });
}

void Obstacle::move() {
	shape.move({ velocity, 0 });
}

void Obstacle::render(sf::RenderWindow& window) {
	window.draw(shape);
}

int Obstacle::getLine() {
	return line;
}

void Obstacle::setPosition(sf::Vector2f pos) {
	shape.setPosition(pos);
}