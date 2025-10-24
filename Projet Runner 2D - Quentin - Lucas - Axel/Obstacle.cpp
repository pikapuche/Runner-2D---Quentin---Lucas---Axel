#include "Obstacle.hpp"

Obstacle::Obstacle(float _velocity, int _line) : line(_line), velocity(_velocity) {
	
	shape.setTextureRect(sf::IntRect({ 0, 32 }, { 96, 64 })); // 1 tile = 32px //// 3 tiles = 96px
	shape.setTexture(&Shared::tileSetTexture);

	safePlaceShape.setTextureRect(sf::IntRect({ 320, 0 }, { 96, 32 }));
	safePlaceShape.setTexture(&Shared::tileSetTexture);
}

Obstacle::~Obstacle() {
}

void Obstacle::init() {
	safePlaceShape.setSize({ static_cast<float>(STGS::WIDTH / 5), static_cast<float>(STGS::HEIGHT * 0.02f)});
	safePlaceShape.setPosition({ shape.getPosition().x, shape.getPosition().y - safePlaceShape.getSize().y });
}

void Obstacle::move(float deltatime, int difficulty) {
	shape.move({ velocity * deltatime, 0 });
	safePlaceShape.move({ velocity * deltatime, 0 });
	switch (difficulty)
	{
	case 1 :
		shape.setFillColor(sf::Color(255, 0, 187, 215));
		safePlaceShape.setFillColor(sf::Color(255, 0, 187, 215));
		break;
	case 2:
		shape.setFillColor(sf::Color(21, 255, 0, 215));
		safePlaceShape.setFillColor(sf::Color(21, 255, 0, 215));
		break;
	case 3:
		break;
	case 4:
		shape.setFillColor(sf::Color(255, 166, 0, 215));
		safePlaceShape.setFillColor(sf::Color(255, 166, 0, 215));
		break;
	default:
		break;
	}
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