#include "HUD.hpp"

HUD::HUD() : scoreText(font), timerText(font), goldText(font), speedText(font) {
	sbstr = 0;
	sbstrSpeed = 0;
	seconds = 0;
}

HUD::~HUD() {}

void HUD::initHUD() {
	if (!font.openFromFile("Assets/Fonts/Minecraft.ttf"))
		std::cerr << "error : load font minecraft" << std::endl;

	goldPieceShape.setTexture(&Shared::goldTexture);
	heart1Shape.setTexture(&Shared::heart1Texture, true);
	heart2Shape.setTexture(&Shared::heart2Texture, true);
	heart3Shape.setTexture(&Shared::heart3Texture, true);

	heart1Shape.setFillColor(sf::Color::White);
	heart2Shape.setFillColor(sf::Color::White);
	heart3Shape.setFillColor(sf::Color::White);

	goldText.setString("0");
	goldText.setCharacterSize({ 60 });
	goldText.setOutlineThickness(5.f);
	goldText.setOutlineColor(sf::Color::Black);
	goldText.setFillColor(sf::Color::Yellow);
	goldText.setPosition({ static_cast<float>(STGS::WIDTH * 0.05f), static_cast<float>(STGS::HEIGHT * 0.9f) });

	goldPieceShape.setSize({ STGS::WIDTH * 0.04f, STGS::WIDTH * 0.04f });
	goldPieceShape.setPosition({ goldText.getPosition().x - goldPieceShape.getGlobalBounds().size.x, static_cast<float>(STGS::HEIGHT * 0.9f) });

	timerText.setString("Timer : 00:00");
	timerText.setCharacterSize({60});
	timerText.setFillColor(sf::Color::White);
	timerText.setOutlineThickness(5.f);
	timerText.setOutlineColor(sf::Color::Black);
	timerText.setPosition({ static_cast<float>(STGS::WIDTH * 0.01), static_cast<float>(STGS::HEIGHT * 0.01) });

	scoreText.setString("Score : 000");
	scoreText.setCharacterSize(60);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setOutlineThickness(5.f);
	scoreText.setOutlineColor(sf::Color::Black);
	scoreText.setPosition({ static_cast<float>(STGS::WIDTH) - scoreText.getGlobalBounds().size.x - static_cast<float>(STGS::WIDTH * 0.01), static_cast<float>(STGS::HEIGHT * 0.01f)});

	heart1Shape.setSize({ static_cast<float>(STGS::WIDTH * 0.05), static_cast<float>(STGS::HEIGHT * 0.07) });
	heart1Shape.setPosition({ static_cast<float>(STGS::WIDTH * 0.01), timerText.getPosition().y + timerText.getGlobalBounds().size.y + static_cast<float>(STGS::HEIGHT * 0.03) });

	heart2Shape.setSize({ static_cast<float>(STGS::WIDTH * 0.05), static_cast<float>(STGS::HEIGHT * 0.07) });
	heart2Shape.setPosition({ heart1Shape.getPosition().x + heart1Shape.getGlobalBounds().size.x + static_cast<float>(STGS::WIDTH * 0.01), timerText.getPosition().y + timerText.getGlobalBounds().size.y + static_cast<float>(STGS::HEIGHT * 0.02) });
	heart2Shape.setScale({ 1.5, 1.5 });

	heart3Shape.setSize({ static_cast<float>(STGS::WIDTH * 0.05), static_cast<float>(STGS::HEIGHT * 0.07) });
	heart3Shape.setPosition({ heart2Shape.getPosition().x + heart2Shape.getGlobalBounds().size.x + static_cast<float>(STGS::WIDTH * 0.001), timerText.getPosition().y + timerText.getGlobalBounds().size.y + static_cast<float>(STGS::HEIGHT * 0.03) });

	speedText.setString("00.00 Km/h");
	speedText.setCharacterSize(60);
	speedText.setFillColor(sf::Color::White);
	speedText.setOutlineThickness(5.f);
	speedText.setOutlineColor(sf::Color::Black);
	speedText.setPosition({ static_cast<float>(STGS::WIDTH * 0.01), heart1Shape.getPosition().y + heart1Shape.getGlobalBounds().size.y + static_cast<float>(STGS::HEIGHT * 0.01f) });
}

void HUD::drawHUD(sf::RenderWindow& window, Player& player) {
	window.draw(scoreText);
	window.draw(timerText);
	window.draw(goldText);
	window.draw(goldPieceShape);
	window.draw(speedText);

	if (player.getLife() == 3) {
		window.draw(heart3Shape);
		window.draw(heart2Shape);
		window.draw(heart1Shape);
	}
	else if (player.getLife() == 2) {
		heart3Shape.setFillColor(sf::Color(96, 96, 96));
		window.draw(heart3Shape);
		window.draw(heart2Shape);
		window.draw(heart1Shape);
	}
	else if (player.getLife() == 1) {
		window.draw(heart3Shape);
		heart2Shape.setFillColor(sf::Color(96, 96, 96));
		window.draw(heart2Shape);
		window.draw(heart1Shape);
	}
}

void HUD::update(sf::Clock& clock, int score, int collectible, float speed) {
	elapsed = clock.getElapsedTime();
	seconds = elapsed.asSeconds();

	sbstr = 4;
	if (seconds >= 10)
		sbstr = 5;
	else if (seconds >= 100)
		sbstr = 6;
	timerText.setString("Timer : " + std::to_string(seconds).substr(0, sbstr));

	if (score < 10)
		scoreText.setString("Score : 00" + std::to_string(score));
	else if (score < 100)
		scoreText.setString("Score : 0" + std::to_string(score));
	else
		scoreText.setString("Score : " + std::to_string(score));

	goldText.setString(std::to_string(collectible));

	sbstrSpeed = 5;
	if (speed >= 100)
		sbstrSpeed = 6;
	speedText.setString(std::to_string(90.f * std::sqrt(speed / 500.f)).substr(0, sbstrSpeed) + " Km/h");
}