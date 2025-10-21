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

		if (line == 0)
			shape.setPosition({ STGS::WIDTH, 0 + STGS::GAP_Y / 2 });
		else if (line == 1)
			shape.setPosition({ STGS::WIDTH, STGS::HEIGHT * 1 / 3 + STGS::GAP_Y / 2 });
		else if (line == 2)
			shape.setPosition({ STGS::WIDTH, STGS::HEIGHT * 2 / 3 + STGS::GAP_Y / 2 });
	
	std::cout << "line : " << line << std::endl;
	std::cout << "pos : " << shape.getPosition().y << std::endl;
	
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