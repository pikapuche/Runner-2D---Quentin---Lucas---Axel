#include "Menu.hpp"
Menu::Menu()
{
	circle.setRadius(50);
	circle.setFillColor(Color::Red);
	initMenu();
}

Menu::~Menu()
{
}
void Menu::initMenu() {
	//setup background
	background.setSize({ 1920,1080 });
	background.setPosition({ 0,0 });
	background.setFillColor(Color::Blue);
}

void Menu::drawMenu(RenderWindow& window) {

	window.draw(background);
}

void Menu::createStartButton() {

}