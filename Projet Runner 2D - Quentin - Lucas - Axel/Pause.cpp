#include "Pause.hpp"
Pause::Pause() : text(textFont) {
	initMenu();
}

Pause::~Pause()
{
}
void Pause::initMenu() {

	//setup background
	background.setSize({ 1920,1080 });
	background.setPosition({ 0,0 });
	background.setFillColor(sf::Color(0, 0, 0, 100));

	//setup backButton
	backButton.buttonState = Button::BACK;
	backButton.buttonBack.setPosition({ 100,800 });
	backButton.buttonBack.setFillColor(sf::Color::White);
	backButton.buttonBack.setSize({ 300,60 });
	backButton.buttonText.setCharacterSize(30);
	backButton.buttonFont.openFromFile("Assets/Fonts/Minecraft.ttf");
	backButton.buttonText.setFont(backButton.buttonFont);
	backButton.buttonText.setString("BACK");
	backButton.buttonText.setPosition({ backButton.buttonBack.getGlobalBounds().size.x / 2 + backButton.buttonText.getGlobalBounds().size.x/2,backButton.buttonBack.getPosition().y + backButton.buttonText.getGlobalBounds().size.y / 2});
	backButton.buttonText.setFillColor(sf::Color::Black);

	//setup resumeButton
	resumeButton.buttonState = Button::RESTART;
	resumeButton.buttonBack.setPosition({ static_cast<float>(STGS::WIDTH * 0.12),700 });
	resumeButton.buttonBack.setFillColor(sf::Color::White);
	resumeButton.buttonBack.setSize({ 300,60 });
	resumeButton.buttonFont.openFromFile("Assets/Fonts/Minecraft.ttf");
	resumeButton.buttonText.setFont(resumeButton.buttonFont);
	resumeButton.buttonText.setString("RESUME");
	resumeButton.buttonText.setPosition({ resumeButton.buttonBack.getGlobalBounds().size.x/2 + resumeButton.buttonText.getGlobalBounds().size.x / 2,resumeButton.buttonBack.getPosition().y + resumeButton.buttonText.getGlobalBounds().size.y / 2 });
	resumeButton.buttonText.setFillColor(sf::Color::Black);

	//setup text
	textFont.openFromFile("Assets/Fonts/Minecraft.ttf");
	text.setFont(textFont);
	text.setString("PAUSE");
	text.setCharacterSize(100);
	text.setFillColor(sf::Color::Green);
	text.setOutlineColor(sf::Color(150, 150, 150));
	text.setOutlineThickness(2);
	text.setPosition({ static_cast<float>(STGS::WIDTH / 2) - text.getGlobalBounds().size.x / 2 ,200 });

}

void Pause::drawMenu(sf::RenderWindow& window) {

	window.draw(background);
	backButton.drawButton(window);
	resumeButton.drawButton(window);
	window.draw(text);
}

void Pause::createStartButton() {

}