#include "Settings.hpp"
SettingsMenu::SettingsMenu() : text(textFont), volumeTextMusic(textFont), volumeTextSoundEffects(textFont) {
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

	//setup text
	text.setFont(textFont);
	text.setString("SETTINGS");
	text.setCharacterSize(100);
	text.setFillColor(sf::Color::White);
	text.setOutlineThickness(5.f);
	text.setOutlineColor(sf::Color::Blue);
	text.setPosition({ static_cast<float>(STGS::WIDTH / 2 - text.getGlobalBounds().size.x / 2 ), static_cast<float>(STGS::HEIGHT * 0.25) });

	// setup volume music
	upMusicShape.setSize({ static_cast<float>(STGS::WIDTH * 0.03), static_cast<float>(STGS::HEIGHT * 0.05) });
	upMusicShape.setPosition({ static_cast<float>(STGS::WIDTH * 0.3), static_cast<float>(STGS::HEIGHT * 0.45) });
	upMusicShape.setFillColor(sf::Color::White);
	upMusicShape.setOutlineThickness(5.f);
	upMusicShape.setOutlineColor(sf::Color::Blue);
	downMusicShape.setSize({ static_cast<float>(STGS::WIDTH * 0.03), static_cast<float>(STGS::HEIGHT * 0.05) });
	downMusicShape.setPosition({ static_cast<float>(STGS::WIDTH * 0.3), static_cast<float>(STGS::HEIGHT * 0.55) });
	downMusicShape.setFillColor(sf::Color::White);
	downMusicShape.setOutlineThickness(5.f);
	downMusicShape.setOutlineColor(sf::Color::Blue);
	volumeTextMusic.setPosition({ static_cast<float>(STGS::WIDTH / 1.9 - downMusicShape.getPosition().x / 2), static_cast<float>(STGS::HEIGHT / 2 - upMusicShape.getGlobalBounds().size.y / 1.5)});
	volumeTextMusic.setFont(textFont);
	volumeTextMusic.setCharacterSize(100);
	volumeTextMusic.setFillColor(sf::Color::Blue);
	volumeTextMusic.setOutlineThickness(5.f);
	volumeTextMusic.setOutlineColor(sf::Color::White);
	volumeTextMusic.setString("error");

	// setop volume sound
	upSoundShape.setSize({ static_cast<float>(STGS::WIDTH * 0.03), static_cast<float>(STGS::HEIGHT * 0.05) });
	upSoundShape.setPosition({ static_cast<float>(STGS::WIDTH * 0.3), static_cast<float>(STGS::HEIGHT * 0.75) });
	upSoundShape.setFillColor(sf::Color::White);
	upSoundShape.setOutlineThickness(5.f);
	upSoundShape.setOutlineColor(sf::Color::Blue);
	downSoundShape.setSize({ static_cast<float>(STGS::WIDTH * 0.03), static_cast<float>(STGS::HEIGHT * 0.05) });
	downSoundShape.setPosition({ static_cast<float>(STGS::WIDTH * 0.3), static_cast<float>(STGS::HEIGHT * 0.85) });
	downSoundShape.setFillColor(sf::Color::White);
	downSoundShape.setOutlineThickness(5.f);
	downSoundShape.setOutlineColor(sf::Color::Blue);
	volumeTextSoundEffects.setPosition({ static_cast<float>(STGS::WIDTH / 1.9 - downSoundShape.getPosition().x / 2), static_cast<float>(STGS::HEIGHT * 0.76) });
	volumeTextSoundEffects.setFont(textFont);
	volumeTextSoundEffects.setCharacterSize(100);
	volumeTextSoundEffects.setFillColor(sf::Color::Blue);
	volumeTextSoundEffects.setOutlineThickness(5.f);
	volumeTextSoundEffects.setOutlineColor(sf::Color::White);
	volumeTextSoundEffects.setString("error");

	clickDelay = 0.1f;
}

void SettingsMenu::setVolume(int& volumeSound, int& volumeMusic)
{
	mousePos = sf::Mouse::getPosition();
	mousePosF.x = static_cast<float>(mousePos.x);
	mousePosF.y = static_cast<float>(mousePos.y);

	if (clickClock.getElapsedTime().asSeconds() > clickDelay) {
		if (upMusicShape.getGlobalBounds().contains(mousePosF) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			volumeMusic++;
			clickClock.restart();
		}
		else if (downMusicShape.getGlobalBounds().contains(mousePosF) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			volumeMusic--;
			clickClock.restart();
		}

		//////// 

		if (upSoundShape.getGlobalBounds().contains(mousePosF) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			volumeSound++;
			clickClock.restart();
		}
		else if (downSoundShape.getGlobalBounds().contains(mousePosF) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			volumeSound--;
			clickClock.restart();
		}
	}
	volumeTextMusic.setString("Music Volume : " + std::to_string(volumeMusic));
	Shared::music.setVolume(volumeMusic);
	Shared::musicMenu.setVolume(volumeMusic);
	volumeTextSoundEffects.setString("Effects Volume : " + std::to_string(volumeSound));
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
