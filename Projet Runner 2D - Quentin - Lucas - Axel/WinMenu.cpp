#include "WinMenu.hpp"

WinMenu::WinMenu() : text(textFont), scoreText(textFont) {
	initMenu();
}

WinMenu::~WinMenu() {}

void WinMenu::initMenu() {
	if (!textFont.openFromFile("Assets/Fonts/Minecraft.ttf"))
		std::cerr << "error : to load minecraft font" << std::endl;

	background.setSize({ static_cast<float>(STGS::WIDTH), static_cast<float>(STGS::HEIGHT) });
	background.setPosition({ 0,0 });
	background.setTexture(&Shared::winBackgroundMenu);

	backButton.buttonState = Button::BACK;
	backButton.buttonBack.setSize({ static_cast<float>(STGS::WIDTH * 0.4), static_cast<float>(STGS::HEIGHT * 0.06) });
	backButton.buttonBack.setPosition({ static_cast<float>(STGS::WIDTH / 2) - backButton.buttonBack.getGlobalBounds().size.x / 2, static_cast<float>(STGS::HEIGHT * 0.8) });
	backButton.buttonBack.setFillColor(sf::Color::White);

	backButton.buttonText.setFont(textFont);
	backButton.buttonText.setCharacterSize(30);
	backButton.buttonText.setString("BACK");
	backButton.buttonText.setPosition({ static_cast<float>(STGS::WIDTH / 2) - backButton.buttonText.getGlobalBounds().size.x / 2 ,backButton.buttonBack.getPosition().y + backButton.buttonText.getGlobalBounds().size.y / 2 });
	backButton.buttonText.setFillColor(sf::Color::Green);

	restartButton.buttonState = Button::RESTART;
	restartButton.buttonBack.setSize({ static_cast<float>(STGS::WIDTH * 0.4), static_cast<float>(STGS::HEIGHT * 0.06) });
	restartButton.buttonBack.setPosition({ static_cast<float>(STGS::WIDTH / 2) - restartButton.buttonBack.getGlobalBounds().size.x / 2, static_cast<float>(STGS::HEIGHT * 0.7) });
	restartButton.buttonBack.setFillColor(sf::Color::White);

	restartButton.buttonText.setCharacterSize(30);
	restartButton.buttonText.setFont(textFont);
	restartButton.buttonText.setString("RESTART");
	restartButton.buttonText.setPosition({ static_cast<float>(STGS::WIDTH / 2) - restartButton.buttonText.getGlobalBounds().size.x / 2 ,restartButton.buttonBack.getPosition().y + restartButton.buttonText.getGlobalBounds().size.y / 2 });
	restartButton.buttonText.setFillColor(sf::Color::Green);

	text.setFont(textFont);
	text.setString("WINNER");
	text.setCharacterSize(100);
	text.setFillColor(sf::Color::Green);
	text.setOutlineColor(sf::Color(150, 150, 150));
	text.setOutlineThickness(2);
	text.setPosition({ static_cast<float>(STGS::WIDTH / 2) - text.getGlobalBounds().size.x / 2 ,200 });

	scoreText.setFont(textFont);
	scoreText.setCharacterSize(50);
	scoreText.setFillColor(sf::Color::Red);
	scoreText.setPosition({ static_cast<float>(STGS::WIDTH / 2) - scoreText.getGlobalBounds().size.x / 2 ,400 });
}

void WinMenu::drawMenu(sf::RenderWindow& window, int score) {
	window.draw(background);
	backButton.drawButton(window);
	restartButton.drawButton(window);
	window.draw(text);
	scoreText.setString("SCORE : " + std::to_string(score));
	window.draw(scoreText);
}

void WinMenu::createStartButton() {
	//PASS
}