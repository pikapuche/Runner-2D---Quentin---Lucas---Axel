#include "Menu.hpp"
Menu::Menu()
{
	circle.setRadius(50);
	circle.setFillColor(Color::Red);
}

Menu::~Menu()
{
}

void Menu::Start(RenderWindow& window) {

	window.draw(circle);
}

void Menu::createStartButton() {

}