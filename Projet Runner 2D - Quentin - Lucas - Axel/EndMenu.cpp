#include "EndMenu.hpp"

EndMenu::EndMenu() : text(textFont), scoreText(textFont) {
	initMenu();
}

EndMenu::~EndMenu() {}

void EndMenu::initMenu() {
	if (!backButton.buttonFont.openFromFile("Assets/Fonts/Minecraft.ttf"))
		std::cerr << "error : to load minecraft font" << std::endl;

	background.setSize({ static_cast<float>(STGS::WIDTH), static_cast<float>(STGS::HEIGHT) });
	background.setPosition({ 0,0 });
	background.setTexture(&Shared::loseBackgroundMenu);

	backButton.buttonState = Button::BACK;
	backButton.buttonBack.setFillColor(sf::Color::White);
	backButton.buttonBack.setSize({ static_cast<float>(STGS::WIDTH * 0.4), static_cast<float>(STGS::HEIGHT * 0.06) });
	backButton.buttonBack.setPosition({ static_cast<float>(STGS::WIDTH / 2) - backButton.buttonBack.getGlobalBounds().size.x / 2, static_cast<float>(STGS::HEIGHT * 0.8) });
	
	backButton.buttonText.setFont(backButton.buttonFont);
	backButton.buttonText.setString("BACK");
	backButton.buttonText.setCharacterSize(30);
	backButton.buttonText.setPosition({ static_cast<float>(STGS::WIDTH / 2) - backButton.buttonText.getGlobalBounds().size.x / 2, backButton.buttonBack.getPosition().y + backButton.buttonText.getGlobalBounds().size.y / 2 });
	backButton.buttonText.setFillColor(sf::Color::Red);

	restartButton.buttonState = Button::RESTART;
	restartButton.buttonBack.setFillColor(sf::Color::White);
	restartButton.buttonBack.setSize({ static_cast<float>(STGS::WIDTH * 0.4), static_cast<float>(STGS::HEIGHT * 0.06) });
	restartButton.buttonBack.setPosition({ static_cast<float>(STGS::WIDTH / 2) - restartButton.buttonBack.getGlobalBounds().size.x / 2, static_cast<float>(STGS::HEIGHT * 0.7) });

	restartButton.buttonText.setFont(backButton.buttonFont);
	restartButton.buttonText.setString("RESTART");
	restartButton.buttonText.setCharacterSize(30);
	restartButton.buttonText.setPosition({ static_cast<float>(STGS::WIDTH / 2) - restartButton.buttonText.getGlobalBounds().size.x / 2 ,restartButton.buttonBack.getPosition().y + restartButton.buttonText.getGlobalBounds().size.y / 2 });
	restartButton.buttonText.setFillColor(sf::Color::Red);

	text.setFont(backButton.buttonFont);
	text.setString("GAME OVER");
	text.setCharacterSize(100);
	text.setFillColor(sf::Color::Red);
	text.setOutlineColor(sf::Color(150, 150, 150));
	text.setOutlineThickness(2);
	text.setPosition({ static_cast<float>(STGS::WIDTH / 2) - text.getGlobalBounds().size.x / 2, static_cast<float>(STGS::HEIGHT * 0.2) });

	scoreText.setFont(textFont);
	scoreText.setCharacterSize(50);
	scoreText.setFillColor(sf::Color::Red);
	scoreText.setPosition({ static_cast<float>(STGS::WIDTH / 2) - scoreText.getGlobalBounds().size.x / 2, static_cast<float>(STGS::HEIGHT * 0.4) });
}

void EndMenu::drawMenu(sf::RenderWindow& window, int score) {
	window.draw(background);

	backButton.drawButton(window);
	restartButton.drawButton(window);
	window.draw(text);

	scoreText.setString("SCORE : " + std::to_string(score));
	window.draw(scoreText);
}

void EndMenu::createStartButton() {
	//PASS
}