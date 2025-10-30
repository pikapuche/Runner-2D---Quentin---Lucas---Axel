#include "WinMenu.hpp"
WinMenu::WinMenu() : text(textFont), scoreText(textFont){
	initMenu();
}

WinMenu::~WinMenu()
{
}
void WinMenu::initMenu() {

	//setup background
	background.setSize({ 1920,1080 });
	background.setPosition({ 0,0 });
	background.setTexture(&Shared::winBackgroundMenu);

	//setup backButton
	backButton.buttonState = Button::BACK;
	backButton.buttonBack.setSize({ 300,60 });
	backButton.buttonBack.setPosition({ static_cast<float>(STGS::WIDTH / 2) - backButton.buttonBack.getGlobalBounds().size.x / 2 ,800 });
	backButton.buttonBack.setFillColor(sf::Color::White);
	restartButton.buttonText.setCharacterSize(30);
	backButton.buttonFont.openFromFile("Assets/Fonts/Minecraft.ttf");
	backButton.buttonText.setFont(backButton.buttonFont);
	backButton.buttonText.setString("BACK");
	backButton.buttonText.setPosition({ static_cast<float>(STGS::WIDTH / 2) - backButton.buttonText.getGlobalBounds().size.x / 2 ,backButton.buttonBack.getPosition().y + backButton.buttonText.getGlobalBounds().size.y / 2 });
	backButton.buttonText.setFillColor(sf::Color::Green);

	//setup restartButton
	restartButton.buttonState = Button::RESTART;
	restartButton.buttonBack.setSize({ 300,60 });
	restartButton.buttonBack.setPosition({ static_cast<float>(STGS::WIDTH / 2) - restartButton.buttonBack.getGlobalBounds().size.x / 2 ,700 });
	restartButton.buttonBack.setFillColor(sf::Color::White);
	restartButton.buttonText.setCharacterSize(30);
	restartButton.buttonFont.openFromFile("Assets/Fonts/Minecraft.ttf");
	restartButton.buttonText.setFont(restartButton.buttonFont);
	restartButton.buttonText.setString("RESTART");
	restartButton.buttonText.setPosition({ static_cast<float>(STGS::WIDTH / 2) - restartButton.buttonText.getGlobalBounds().size.x / 2 ,restartButton.buttonBack.getPosition().y + restartButton.buttonText.getGlobalBounds().size.y / 2 });
	restartButton.buttonText.setFillColor(sf::Color::Green);

	//setup text
	textFont.openFromFile("Assets/Fonts/Minecraft.ttf");
	text.setFont(textFont);
	text.setString("EZ WIN");
	text.setCharacterSize(100);
	text.setFillColor(sf::Color::Green);
	text.setOutlineColor(sf::Color(150, 150, 150));
	text.setOutlineThickness(2);
	text.setPosition({ static_cast<float>(STGS::WIDTH / 2) - text.getGlobalBounds().size.x / 2 ,200 });

	//setup scoreText
	scoreText.setFont(textFont);
	scoreText.setCharacterSize(50);
	scoreText.setFillColor(sf::Color::Red);
	scoreText.setPosition({ static_cast<float>(STGS::WIDTH / 2) - scoreText.getGlobalBounds().size.x / 2 ,400 });
}

void WinMenu::drawMenu(sf::RenderWindow& window, int& score) {

	window.draw(background);
	backButton.drawButton(window);
	restartButton.drawButton(window);
	window.draw(text);
	scoreText.setString("SCORE : " + std::to_string(score));
	window.draw(scoreText);
}

void WinMenu::createStartButton() {

}