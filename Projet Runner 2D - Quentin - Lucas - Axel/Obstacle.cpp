#include "Obstacle.hpp"

Obstacle::Obstacle(float _velocity, int _line) : line(_line), velocity(_velocity) {
	
}

Obstacle::~Obstacle() {
}

void Obstacle::init() {
	
	
	std::cout << "line : " << line << std::endl;
	std::cout << "pos : " << shape.getPosition().y << std::endl;
	
}

void Obstacle::move(float deltatime) {
	shape.move({ velocity * deltatime, 0 });
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