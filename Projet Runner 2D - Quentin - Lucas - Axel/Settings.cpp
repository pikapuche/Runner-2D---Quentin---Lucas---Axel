#include "Settings.hpp"
SettingsMenu::SettingsMenu() : text(textFont) {
	initMenu();
}

SettingsMenu::~SettingsMenu() {}

void SettingsMenu::initMenu() {
	if (!textFont.openFromFile("Assets/Fonts/Minecraft.ttf"))
		std::cerr << "error : to load minecraft font" << std::endl;

	background.setSize({ static_cast<float>(STGS::WIDTH), static_cast<float>(STGS::HEIGHT) });
	background.setPosition({ 0,0 });
	background.setTexture(&Shared::backgroundMenu);

	backButton.buttonState = Button::BACK;
	backButton.buttonBack.setFillColor(sf::Color::White);
	backButton.buttonBack.setSize({ static_cast<float>(STGS::WIDTH * 0.4), static_cast<float>(STGS::HEIGHT * 0.06) });
	backButton.buttonBack.setPosition({ static_cast<float>(STGS::WIDTH * 0.01), static_cast<float>(STGS::HEIGHT / 2) });

	backButton.buttonText.setFont(textFont);
	backButton.buttonText.setString("BACK");
	backButton.buttonText.setFillColor(sf::Color::Yellow);
	backButton.buttonText.setPosition({ backButton.buttonBack.getPosition().x + backButton.buttonBack.getGlobalBounds().size.x / 2 - backButton.buttonText.getGlobalBounds().size.x / 2, backButton.buttonBack.getPosition().y + backButton.buttonBack.getGlobalBounds().size.y / 2 - backButton.buttonText.getGlobalBounds().size.y / 2 });

	text.setFont(textFont);
	text.setString("SETTINGS");
	text.setCharacterSize(100);
	text.setFillColor(sf::Color::Green);
	text.setPosition({ static_cast<float>(STGS::WIDTH / 2 - text.getGlobalBounds().size.x / 2), static_cast<float>(STGS::HEIGHT * 0.4) });
}

void SettingsMenu::drawMenu(sf::RenderWindow& window) {

	window.draw(background);
	backButton.drawButton(window);
	restartButton.drawButton(window);
	window.draw(text);
}

void SettingsMenu::createStartButton() {

}