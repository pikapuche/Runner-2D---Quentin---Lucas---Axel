#pragma once

#include "Collectible.hpp"

Collectible::Collectible(float _velocity, int _line) : line(_line), velocity(_velocity) {
	if (!shapeTexture.loadFromFile("Assets/tiles_map/RunnerTileSet.png")) {
		std::cerr << "Erreur chargement texture" << std::endl;
	}
	shape.setTextureRect(sf::IntRect({ 32, 32 }, { 96, 96 })); // 1 tile = 32px //// 3 tiles = 96px
	shape.setTexture(&shapeTexture);
	shape.setFillColor(sf::Color::Green);
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