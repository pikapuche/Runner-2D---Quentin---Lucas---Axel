#pragma once

#include "Plateform.hpp"

Plateform::Plateform(float _velocity, int _line) : line(_line), velocity(_velocity) {
	shape.setTexture(&Shared::tileSetTexture);
	shape.setTextureRect(sf::IntRect({ 320, 0 }, { 96, 16 }));
	shape.setFillColor(sf::Color::Green);
}

Plateform::~Plateform() {
}

void Plateform::init() {
	std::cout << "line : " << line << std::endl;
	std::cout << "pos : " << shape.getPosition().y << std::endl;
}

void Plateform::move(float deltatime, int difficulty) {
	shape.move({ velocity * deltatime, 0 });

	switch (difficulty) {
	case 1:
		shape.setFillColor(sf::Color(255, 0, 187, 215));
		break;
	case 2:
		shape.setFillColor(sf::Color(21, 255, 0, 215));
		break;
	case 3:
		shape.setFillColor(sf::Color::White);
		break;
	case 4:
		shape.setFillColor(sf::Color(255, 166, 0, 215));
		break;
	default:
		break;
	}
}

void Plateform::render(sf::RenderWindow& window) { 
	window.draw(shape); 
}

int Plateform::getLine() { return line; }
void Plateform::setPosition(sf::Vector2f pos) { shape.setPosition(pos); }