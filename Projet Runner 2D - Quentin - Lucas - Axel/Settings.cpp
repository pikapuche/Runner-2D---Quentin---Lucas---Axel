#include "Settings.hpp"
SettingsMenu::SettingsMenu() : text(textFont) {
	initMenu();
}

SettingsMenu::~SettingsMenu()
{
}
void SettingsMenu::initMenu() {

	//setup background
	background.setSize({ static_cast<float>(STGS::WIDTH), static_cast<float>(STGS::HEIGHT) });
	background.setPosition({ 0,0 });
	background.setTexture(&Shared::backgroundMenu);

	//setup backButton
	backButton.buttonState = Button::BACK;
	backButton.buttonBack.setPosition({ static_cast<float>(STGS::WIDTH * 0.01), static_cast<float>(STGS::HEIGHT / 2) });
	backButton.buttonBack.setFillColor(sf::Color::White);
	backButton.buttonBack.setSize({ 300,60 });
	backButton.buttonText.setPosition({ 100,800 });
	backButton.buttonFont.openFromFile("Assets/Fonts/Minecraft.ttf");
	backButton.buttonText.setFont(backButton.buttonFont);
	backButton.buttonText.setString("BACK");
	backButton.buttonText.setFillColor(sf::Color::Yellow);

	//setup text
	textFont.openFromFile("Assets/Fonts/Minecraft.ttf");
	text.setFont(textFont);
	text.setString("SETTINGS");
	text.setCharacterSize(100);
	text.setFillColor(sf::Color::Green);
	text.setPosition({ 700,300 });

}

void SettingsMenu::drawMenu(sf::RenderWindow& window) {

	window.draw(background);
	backButton.drawButton(window);
	restartButton.drawButton(window);
	window.draw(text);
}

void updateSettings() {

}
void SettingsMenu::createStartButton() {

}