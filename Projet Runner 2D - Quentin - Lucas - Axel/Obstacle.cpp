#include "Obstacle.hpp"

Obstacle::Obstacle(float _velocity, int _line) : line(_line), velocity(_velocity) {
	if (!shapeTexture.loadFromFile("Assets/tiles_map/RunnerTileSet.png")) {
		std::cerr << "Erreur chargement texture" << std::endl;
	}
	shape.setTextureRect(sf::IntRect({ 0, 0 }, { 96, 96 })); // 1 tile = 32px //// 3 tiles = 96px
	shape.setTexture(&shapeTexture);
}

Obstacle::~Obstacle() {
}

void Obstacle::init() {
	safePlaceShape.setSize({ STGS::WIDTH / 5, STGS::HEIGHT * 0.02f});
	safePlaceShape.setPosition({ shape.getPosition().x, shape.getPosition().y - safePlaceShape.getSize().y });
	safePlaceShape.setFillColor(sf::Color::Green);
}

void Obstacle::move(float deltatime) {
	shape.move({ velocity * deltatime, 0 });
	safePlaceShape.move({ velocity * deltatime, 0 });
}

void Obstacle::render(sf::RenderWindow& window) {
	window.draw(shape);
	window.draw(safePlaceShape);
}

int Obstacle::getLine() {
	return line;
}

void Obstacle::setPosition(sf::Vector2f pos) {
	shape.setPosition(pos);
}

sf::FloatRect Obstacle::getSafePlaceBounds() {
	return safePlaceShape.getGlobalBounds();
}