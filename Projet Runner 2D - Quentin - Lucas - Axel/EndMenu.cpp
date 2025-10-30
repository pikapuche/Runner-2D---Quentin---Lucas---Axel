#include "EndMenu.hpp"
EndMenu::EndMenu() : text(textFont){
	initMenu();
}

EndMenu::~EndMenu()
{
}
void EndMenu::initMenu() {

	//setup background
	background.setSize({ 1920,1080 });
	background.setPosition({ 0,0 });
	background.setTexture(&Shared::loseBackgroundMenu);

	//setup backButton
	backButton.buttonState = Button::BACK;
	backButton.buttonBack.setFillColor(sf::Color::White);
	backButton.buttonBack.setSize({ 300,60 });
	backButton.buttonBack.setPosition({ static_cast<float>(STGS::WIDTH / 2) - backButton.buttonBack.getGlobalBounds().size.x / 2 ,800 });
	backButton.buttonFont.openFromFile("Assets/Fonts/Minecraft.ttf");
	backButton.buttonText.setFont(backButton.buttonFont);
	backButton.buttonText.setString("BACK");
	backButton.buttonText.setCharacterSize(30);
	backButton.buttonText.setPosition({ static_cast<float>(STGS::WIDTH / 2) - backButton.buttonText.getGlobalBounds().size.x / 2 ,backButton.buttonBack.getPosition().y + backButton.buttonText.getGlobalBounds().size.y / 2 });
	backButton.buttonText.setFillColor(sf::Color::Red);

	//setup restartButton
	restartButton.buttonState = Button::RESTART;
	restartButton.buttonBack.setFillColor(sf::Color::White);
	restartButton.buttonBack.setSize({ 300,60 });
	restartButton.buttonBack.setPosition({ static_cast<float>(STGS::WIDTH / 2) - restartButton.buttonBack.getGlobalBounds().size.x / 2 ,700 });
	restartButton.buttonFont.openFromFile("Assets/Fonts/Minecraft.ttf");
	restartButton.buttonText.setFont(restartButton.buttonFont);
	restartButton.buttonText.setString("RESTART");
	restartButton.buttonText.setCharacterSize(30);
	restartButton.buttonText.setPosition({ static_cast<float>(STGS::WIDTH / 2) - restartButton.buttonText.getGlobalBounds().size.x / 2 ,restartButton.buttonBack.getPosition().y + restartButton.buttonText.getGlobalBounds().size.y / 2 });
	restartButton.buttonText.setFillColor(sf::Color::Red);

	//setup text
	textFont.openFromFile("Assets/Fonts/Minecraft.ttf");
	text.setFont(textFont);
	text.setString("GAME OVER");
	text.setCharacterSize(100);
	text.setFillColor(sf::Color::Red);
	text.setOutlineColor(sf::Color(150,150,150));
	text.setOutlineThickness(2);
	text.setPosition({ static_cast<float>(STGS::WIDTH / 2) - text.getGlobalBounds().size.x / 2 ,200 });

}

void EndMenu::drawMenu(sf::RenderWindow& window) {

	window.draw(background);
	backButton.drawButton(window);
	restartButton.drawButton(window);
	window.draw(text);
}

void EndMenu::createStartButton() {

}