#include "MenuStart.hpp"

MenuStart::MenuStart() {

}

MenuStart::~MenuStart() {

}

void MenuStart::initMenu() {

}

void MenuStart::drawButtons(sf::RenderWindow& window) {
	for (auto& button : m_buttons)
	{
		if (!button) continue;
		button->draw(window);
	}
}

void MenuStart::drawUis(sf::RenderWindow& window) {
	for (auto& ui : m_allUis)
	{
		if (!ui) continue;
		ui->draw(window);
	}
}
void MenuStart::drawAll(sf::RenderWindow& window) {
	drawUis(window);
	drawButtons(window);
}