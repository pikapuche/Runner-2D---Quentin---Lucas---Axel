#pragma once

#include "Collectible.hpp"

Collectible::Collectible(float _velocity, int _line) : line(_line), velocity(_velocity) {
	shape.setTexture(&Shared::collectibleTexture);
}

Collectible::~Collectible() {
}

void Collectible::init() {
	//std::cout << "line : " << line << std::endl;
	//std::cout << "pos : " << shape.getPosition().y << std::endl;
}

void Collectible::move(float deltatime) {
	shape.move({ velocity * deltatime, 0 });
}

void Collectible::render(sf::RenderWindow& window) {
	window.draw(shape);
}

int Collectible::getLine() {
	return line;
}

void Collectible::setPosition(sf::Vector2f pos) {
	shape.setPosition(pos);
}