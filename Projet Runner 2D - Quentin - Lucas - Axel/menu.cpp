#include "Menu.hpp"

Menu::Menu() : gameTitle(font) {
	initMenu();
}

Menu::~Menu() {}

void Menu::initMenu() {
	if (!font.openFromFile("Assets/Fonts/Minecraft.ttf"))
		std::cerr << "error : to open minecraft font" << std::endl;
	background.setSize({ static_cast<float>(STGS::WIDTH), static_cast<float>(STGS::HEIGHT) });
	background.setPosition({ 0,0 });
	background.setTexture(&Shared::backgroundMenu);

	playButton.buttonState = Button::PLAY;
	playButton.buttonBack.setSize({ static_cast<float>(STGS::WIDTH * 0.4), static_cast<float>(STGS::HEIGHT * 0.06) });
	playButton.buttonBack.setPosition({ static_cast<float>(STGS::WIDTH/2) - playButton.buttonBack.getGlobalBounds().size.x/2, static_cast<float>(STGS::HEIGHT * 0.7) });
	playButton.buttonBack.setFillColor(sf::Color::White);

	playButton.buttonText.setString("PLAY");
	playButton.buttonText.setCharacterSize(30);
	playButton.buttonText.setFont(font);
	playButton.buttonText.setPosition({ static_cast<float>(STGS::WIDTH / 2) - playButton.buttonText.getGlobalBounds().size.x / 2 ,playButton.buttonBack.getPosition().y + playButton.buttonText.getGlobalBounds().size.y / 2});
	playButton.buttonText.setFillColor(sf::Color::Blue);

	quitButton.buttonState = Button::QUIT;
	quitButton.buttonBack.setSize({ static_cast<float>(STGS::WIDTH * 0.4), static_cast<float>(STGS::HEIGHT * 0.06) });
	quitButton.buttonBack.setPosition({ static_cast<float>(STGS::WIDTH / 2) - quitButton.buttonBack.getGlobalBounds().size.x / 2, static_cast<float>(STGS::HEIGHT * 0.9) });
	quitButton.buttonBack.setFillColor(sf::Color::White);

	quitButton.buttonText.setString("QUIT");
	quitButton.buttonText.setFont(font);
	quitButton.buttonText.setPosition({ static_cast<float>(STGS::WIDTH / 2) - quitButton.buttonText.getGlobalBounds().size.x / 2 ,quitButton.buttonBack.getPosition().y + quitButton.buttonText.getGlobalBounds().size.y / 2 });
	quitButton.buttonText.setFillColor(sf::Color::Blue);

	settingsButton.buttonState = Button::QUIT;
	settingsButton.buttonBack.setSize({ static_cast<float>(STGS::WIDTH * 0.4), static_cast<float>(STGS::HEIGHT * 0.06) });
	settingsButton.buttonBack.setPosition({ static_cast<float>(STGS::WIDTH / 2) - settingsButton.buttonBack.getGlobalBounds().size.x / 2, static_cast<float>(STGS::HEIGHT * 0.8) });
	settingsButton.buttonBack.setFillColor(sf::Color::White);

	settingsButton.buttonText.setString("SETTINGS");
	settingsButton.buttonText.setFont(font);
	settingsButton.buttonText.setPosition({ static_cast<float>(STGS::WIDTH / 2) - settingsButton.buttonText.getGlobalBounds().size.x / 2 ,settingsButton.buttonBack.getPosition().y + settingsButton.buttonText.getGlobalBounds().size.y / 2 });
	settingsButton.buttonText.setFillColor(sf::Color::Blue);

	gameTitle.setCharacterSize(100);
	gameTitle.setString("THE PINK PARADOX");
	gameTitle.setOutlineColor(sf::Color::Black);
	gameTitle.setOutlineThickness(2);
	gameTitle.setPosition({ static_cast<float>(STGS::WIDTH / 2) - gameTitle.getGlobalBounds().size.x / 2, static_cast<float>(STGS::HEIGHT * 0.4)});
}

void Menu::drawMenu(sf::RenderWindow& window) {
	window.draw(background);
	window.draw(gameTitle);
	playButton.drawButton(window);
	playButton.drawButton(window);
	quitButton.drawButton(window);
	settingsButton.drawButton(window);
}
