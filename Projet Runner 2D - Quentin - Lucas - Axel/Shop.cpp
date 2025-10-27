#include "Shop.hpp"

Shop::Shop() {
	shopBackgroundShape.setSize(sf::Vector2f(static_cast<float>(STGS::WIDTH), static_cast<float>(STGS::HEIGHT)));
	shopBackgroundShape.setPosition({ 0, 0 });
	shopBackgroundShape.setFillColor(sf::Color::Red);
}

Shop::~Shop() {}

void Shop::update() {

}

void Shop::render(sf::RenderWindow& window) {
	window.draw(shopBackgroundShape);
}