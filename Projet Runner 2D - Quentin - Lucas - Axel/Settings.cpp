#include "Settings.hpp"
SettingsMenu::SettingsMenu() : text(textFont) {
	initMenu();
}

SettingsMenu::~SettingsMenu()
{
}
void SettingsMenu::initMenu() {

	//setup background
	background.setSize({ 1920,1080 });
	background.setPosition({ 0,0 });
	background.setTexture(&Shared::backgroundMenu);

	//setup backButton
	backButton.buttonState = Button::BACK;
	backButton.buttonBack.setPosition({ 100,800 });
	backButton.buttonBack.setFillColor(sf::Color::White);
	backButton.buttonBack.setSize({ 300,60 });
	backButton.buttonText.setPosition({ 100,800 });
	backButton.buttonFont.openFromFile("Assets/Fonts/Minecraft.ttf");
	backButton.buttonText.setFont(backButton.buttonFont);
	backButton.buttonText.setString("BACK");
	backButton.buttonText.setFillColor(sf::Color::Yellow);

	//setup restartButton
	restartButton.buttonState = Button::RESTART;
	restartButton.buttonBack.setPosition({ 100,700 });
	restartButton.buttonBack.setFillColor(sf::Color::White);
	restartButton.buttonBack.setSize({ 300,60 });
	restartButton.buttonText.setPosition({ 100,700 });
	restartButton.buttonFont.openFromFile("Assets/Fonts/Minecraft.ttf");
	restartButton.buttonText.setFont(restartButton.buttonFont);
	restartButton.buttonText.setString("RESTART");
	restartButton.buttonText.setFillColor(sf::Color::Yellow);

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