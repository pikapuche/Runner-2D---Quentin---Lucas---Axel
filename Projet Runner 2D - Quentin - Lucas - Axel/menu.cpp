#include "Menu.hpp"
Menu::Menu() : gameTitle(titleFont){
	initMenu();
}

Menu::~Menu()
{
}
void Menu::initMenu() {

	titleFont.openFromFile("Assets/Fonts/Minecraft.ttf");
	//setup background
	background.setSize({ 1920,1080 });
	background.setPosition({ 0,0 });
	background.setTexture(&Shared::backgroundMenu);

	//setup playButton
	playButton.buttonState = Button::PLAY;
	playButton.buttonBack.setSize({ 300,60 });
	playButton.buttonBack.setPosition({ static_cast<float>(STGS::WIDTH/2) - playButton.buttonBack.getGlobalBounds().size.x/2 ,700});
	playButton.buttonBack.setFillColor(sf::Color::White);
	playButton.buttonText.setString("PLAY");
	playButton.buttonText.setCharacterSize(30);
	playButton.buttonFont.openFromFile("Assets/Fonts/Minecraft.ttf");
	playButton.buttonText.setFont(playButton.buttonFont);
	playButton.buttonText.setPosition({ static_cast<float>(STGS::WIDTH / 2) - playButton.buttonText.getGlobalBounds().size.x / 2 ,playButton.buttonBack.getPosition().y + playButton.buttonText.getGlobalBounds().size.y / 2});
	playButton.buttonText.setFillColor(sf::Color::Blue);

	//QuitButton
	quitButton.buttonState = Button::QUIT;
	quitButton.buttonBack.setSize({ 300,60 });
	quitButton.buttonBack.setPosition({ static_cast<float>(STGS::WIDTH / 2) - quitButton.buttonBack.getGlobalBounds().size.x / 2 ,900 });
	quitButton.buttonBack.setFillColor(sf::Color::White);
	quitButton.buttonText.setString("QUIT");
	quitButton.buttonFont.openFromFile("Assets/Fonts/Minecraft.ttf");
	quitButton.buttonText.setFont(quitButton.buttonFont);
	quitButton.buttonText.setPosition({ static_cast<float>(STGS::WIDTH / 2) - quitButton.buttonText.getGlobalBounds().size.x / 2 ,quitButton.buttonBack.getPosition().y + quitButton.buttonText.getGlobalBounds().size.y / 2 });
	quitButton.buttonText.setFillColor(sf::Color::Blue);

	//SettingsButton
	settingsButton.buttonState = Button::QUIT;
	settingsButton.buttonBack.setSize({ 300,60 });
	settingsButton.buttonBack.setPosition({ static_cast<float>(STGS::WIDTH / 2) - settingsButton.buttonBack.getGlobalBounds().size.x / 2 ,800 });
	settingsButton.buttonBack.setFillColor(sf::Color::White);
	settingsButton.buttonText.setString("SETTINGS");
	settingsButton.buttonFont.openFromFile("Assets/Fonts/Minecraft.ttf");
	settingsButton.buttonText.setFont(quitButton.buttonFont);
	settingsButton.buttonText.setPosition({ static_cast<float>(STGS::WIDTH / 2) - settingsButton.buttonText.getGlobalBounds().size.x / 2 ,settingsButton.buttonBack.getPosition().y + settingsButton.buttonText.getGlobalBounds().size.y / 2 });
	settingsButton.buttonText.setFillColor(sf::Color::Blue);

	gameTitle.setCharacterSize(100);
	gameTitle.setString("RUNNER 2D");
	gameTitle.setPosition({ static_cast<float>(STGS::WIDTH / 2) - gameTitle.getGlobalBounds().size.x / 2 ,200 });
}

void Menu::drawMenu(sf::RenderWindow& window) {

	window.draw(background);
	window.draw(gameTitle);
	playButton.drawButton(window);
	playButton.drawButton(window);
	quitButton.drawButton(window);
	settingsButton.drawButton(window);
}

void Menu::createStartButton() {

}