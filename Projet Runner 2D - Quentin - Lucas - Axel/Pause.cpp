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
	background.setFillColor(sf::Color::Blue);

	//setup backButton
	backButton.buttonState = Button::BACK;
	backButton.buttonBack.setPosition({ 100,800 });
	backButton.buttonBack.setFillColor(sf::Color::White);
	backButton.buttonBack.setSize({ 300,60 });
	backButton.buttonFont.openFromFile("Assets/Fonts/Minecraft.ttf");
	backButton.buttonText.setFont(backButton.buttonFont);
	backButton.buttonText.setString("BACK");
	backButton.buttonText.setPosition({ 100,800 });
	backButton.buttonText.setFillColor(sf::Color::Yellow);

	//setup resumeButton
	resumeButton.buttonState = Button::RESTART;
	resumeButton.buttonBack.setPosition({ 100,700 });
	resumeButton.buttonBack.setFillColor(sf::Color::White);
	resumeButton.buttonBack.setSize({ 300,60 });
	resumeButton.buttonFont.openFromFile("Assets/Fonts/Minecraft.ttf");
	resumeButton.buttonText.setFont(resumeButton.buttonFont);
	resumeButton.buttonText.setString("RESUME");
	resumeButton.buttonText.setPosition({ 100,700 });
	resumeButton.buttonText.setFillColor(sf::Color::Yellow);

	//setup epilepticButton
	
	epilepticButton.buttonState = Button::RESTART;
	epilepticButton.buttonBack.setPosition({ 100,600 });
	epilepticButton.buttonBack.setFillColor(sf::Color::White);
	epilepticButton.buttonBack.setSize({ 300,60 });
	epilepticButton.buttonFont.openFromFile("Assets/Fonts/Minecraft.ttf");
	epilepticButton.buttonText.setFont(epilepticButton.buttonFont);
	epilepticButton.buttonText.setString("EPILEPTIC MODE");
	epilepticButton.buttonText.setPosition({ 100,600 });
	epilepticButton.buttonText.setFillColor(sf::Color::Blue);


	//setup text
	textFont.openFromFile("Assets/Fonts/Minecraft.ttf");
	text.setFont(textFont);
	text.setCharacterSize(100);
	text.setString("PAUSE");
	text.setFillColor(sf::Color::Green);
	text.setPosition({ 700,300 });

}

void Pause::drawMenu(sf::RenderWindow& window) {

	window.draw(background);
	backButton.drawButton(window);
	resumeButton.drawButton(window);
	epilepticButton.drawButton(window);
	window.draw(text);
}

void Pause::createStartButton() {

}