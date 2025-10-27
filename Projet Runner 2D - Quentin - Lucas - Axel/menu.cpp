#include "Menu.hpp"
Menu::Menu() {
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

	//setup playButton
	playButton.buttonState = Button::PLAY;
	playButton.buttonBack.setPosition({ 100,700 });
	playButton.buttonBack.setFillColor(Color::White);
	playButton.buttonBack.setSize({ 300,60 });
	playButton.buttonText.setPosition({ 100,700 });
	playButton.buttonFont.openFromFile("Assets/Fonts/Minecraft.ttf");
	playButton.buttonText.setFont(playButton.buttonFont);
	playButton.buttonText.setString("PLAY");
	playButton.buttonText.setFillColor(Color::Yellow);

	//QuitButton
	quitButton.buttonState = Button::QUIT;
	quitButton.buttonBack.setPosition({ 100,900 });
	quitButton.buttonBack.setFillColor(Color::White);
	quitButton.buttonBack.setSize({ 300,60 });
	quitButton.buttonText.setPosition({ 100,900 });
	quitButton.buttonFont.openFromFile("Assets/Fonts/Minecraft.ttf");
	quitButton.buttonText.setFont(quitButton.buttonFont);
	quitButton.buttonText.setString("QUIT");
	quitButton.buttonText.setFillColor(Color::Yellow);

	//SettingsButton
	settingsButton.buttonState = Button::QUIT;
	settingsButton.buttonBack.setPosition({ 100,800 });
	settingsButton.buttonBack.setFillColor(Color::White);
	settingsButton.buttonBack.setSize({ 300,60 });
	settingsButton.buttonText.setPosition({ 100,800 });
	settingsButton.buttonFont.openFromFile("Assets/Fonts/Minecraft.ttf");
	settingsButton.buttonText.setFont(quitButton.buttonFont);
	settingsButton.buttonText.setString("SETTINGS");
	settingsButton.buttonText.setFillColor(Color::Yellow);


}

void Menu::drawMenu(RenderWindow& window) {

	window.draw(background);
	playButton.drawButton(window);
	playButton.drawButton(window);
	quitButton.drawButton(window);
	settingsButton.drawButton(window);
}

void Menu::createStartButton() {

}