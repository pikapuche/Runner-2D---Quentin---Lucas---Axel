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

	//setup playButton
	playButton.buttonState = Button::PLAY;
	playButton.buttonBack.setPosition({ 100,900 });
	playButton.buttonBack.setFillColor(Color::White);
	playButton.buttonBack.setSize({ 300,60 });
	playButton.buttonText.setPosition({ 100,900 });
	playButton.buttonFont.openFromFile("Assets/Fonts/Minecraft.ttf");
	playButton.buttonText.setFont(playButton.buttonFont);
	playButton.buttonText.setString("PLAY");
	playButton.buttonText.setFillColor(Color::Yellow);


}

void Menu::drawMenu(RenderWindow& window) {

	window.draw(background);
	playButton.drawButton(window);
}

void Menu::createStartButton() {

}