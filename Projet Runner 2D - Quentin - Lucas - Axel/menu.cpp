#include "Menu.hpp"
Menu::Menu() {
	circle.setRadius(50);
	circle.setFillColor(sf::Color::Red);
}

Menu::~Menu() {}

void Menu::Start(sf::RenderWindow& window) {
	window.draw(circle);
}

void Menu::createStartButton() {

}