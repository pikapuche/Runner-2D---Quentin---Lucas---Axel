#include "Settings.hpp"
SettingsMenu::SettingsMenu() : text(textFont), volumeTextMusic(textFont), volumeTextSoundEffects(textFont) {
	initMenu();
}

SettingsMenu::~SettingsMenu()
{
}

void SettingsMenu::initMenu() {
	textFont.openFromFile("Assets/Fonts/Minecraft.ttf");

	//setup background
	background.setSize({ static_cast<float>(STGS::WIDTH), static_cast<float>(STGS::HEIGHT) });
	background.setPosition({ 0,0 });
	background.setTexture(&Shared::backgroundMenu);

	//setup backButton
	backButton.buttonState = Button::BACK;
	backButton.buttonBack.setPosition({ static_cast<float>(STGS::WIDTH * 0.05), static_cast<float>(STGS::HEIGHT * 0.80) });
	backButton.buttonBack.setFillColor(sf::Color::Blue);
	backButton.buttonBack.setSize({ 300,60 });
	backButton.buttonText.setFont(textFont);
	backButton.buttonText.setString("BACK");
	backButton.buttonText.setFillColor(sf::Color::White);
	backButton.buttonText.setPosition({ backButton.buttonBack.getPosition().x + backButton.buttonText.getGlobalBounds().size.x / 2, backButton.buttonBack.getPosition().y + backButton.buttonText.getGlobalBounds().size.y / 2 });

	//setup text
	text.setFont(textFont);
	text.setString("SETTINGS");
	text.setCharacterSize(100);
	text.setFillColor(sf::Color::White);
	text.setOutlineThickness(5.f);
	text.setOutlineColor(sf::Color::Blue);
	text.setPosition({ static_cast<float>(STGS::WIDTH / 2 - text.getGlobalBounds().size.x / 2 ), static_cast<float>(STGS::HEIGHT * 0.25) });

	// setup volume music
	upMusicShape.setSize({ static_cast<float>(STGS::WIDTH * 0.01), static_cast<float>(STGS::HEIGHT * 0.01) });
	upMusicShape.setPosition({ static_cast<float>(STGS::WIDTH * 0.7), static_cast<float>(STGS::HEIGHT * 0.6) });
	upMusicShape.setFillColor(sf::Color::Blue);
	upMusicShape.setOutlineThickness(5.f);
	upMusicShape.setOutlineColor(sf::Color::White);
	downMusicShape.setSize({ static_cast<float>(STGS::WIDTH * 0.01), static_cast<float>(STGS::HEIGHT * 0.01) });
	downMusicShape.setPosition({ static_cast<float>(STGS::WIDTH * 0.7), static_cast<float>(STGS::HEIGHT * 0.7) });
	downMusicShape.setFillColor(sf::Color::Blue);
	downMusicShape.setOutlineThickness(5.f);
	downMusicShape.setOutlineColor(sf::Color::White);
	volumeTextMusic.setFont(textFont);
	volumeTextMusic.setCharacterSize(100);
	volumeTextMusic.setFillColor(sf::Color::Blue);
	volumeTextMusic.setOutlineThickness(5.f);
	volumeTextMusic.setOutlineColor(sf::Color::White);

	// setop volume sound
	upSoundShape.setSize({ static_cast<float>(STGS::WIDTH * 0.01), static_cast<float>(STGS::HEIGHT * 0.01) });
	upSoundShape.setPosition({ static_cast<float>(STGS::WIDTH * 0.7), static_cast<float>(STGS::HEIGHT * 0.6) });
	upSoundShape.setFillColor(sf::Color::Blue);
	upSoundShape.setOutlineThickness(5.f);
	upSoundShape.setOutlineColor(sf::Color::White);
	downSoundShape.setSize({ static_cast<float>(STGS::WIDTH * 0.01), static_cast<float>(STGS::HEIGHT * 0.01) });
	downSoundShape.setPosition({ static_cast<float>(STGS::WIDTH * 0.7), static_cast<float>(STGS::HEIGHT * 0.7) });
	downSoundShape.setFillColor(sf::Color::Blue);
	downSoundShape.setOutlineThickness(5.f);
	downSoundShape.setOutlineColor(sf::Color::White);
	volumeTextSoundEffects.setFont(textFont);
	volumeTextSoundEffects.setCharacterSize(100);
	volumeTextSoundEffects.setFillColor(sf::Color::Blue);
	volumeTextSoundEffects.setOutlineThickness(5.f);
	volumeTextSoundEffects.setOutlineColor(sf::Color::White);
}

void SettingsMenu::setVolume(int& volumeSound, int& volumeMusic)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition();
	sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

	if (upMusicShape.getGlobalBounds().contains(mousePosF) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		volumeMusic++;
	}
	else if (downMusicShape.getGlobalBounds().contains(mousePosF) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		volumeMusic--;
	}
	volumeTextMusic.setString("Volume musique : " + std::to_string(volumeMusic));

	//////// 

	if (upSoundShape.getGlobalBounds().contains(mousePosF) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		volumeSound++;
	}
	else if (downSoundShape.getGlobalBounds().contains(mousePosF) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		volumeSound--;
	}
	volumeTextSoundEffects.setString("Volume sons et effets : " + std::to_string(volumeSound));
}

void SettingsMenu::drawMenu(sf::RenderWindow& window) {

	window.draw(background);
	backButton.drawButton(window);
	restartButton.drawButton(window);
	window.draw(text);

	window.draw(upMusicShape);
	window.draw(downMusicShape);
	window.draw(volumeTextMusic);

	window.draw(upSoundShape);
	window.draw(downSoundShape);
	window.draw(volumeTextSoundEffects);
}



void SettingsMenu::updateSettings()
{
}
