#include "HUD.hpp"

HUD::HUD() : score(font), timer(font), gold(font) {
}

HUD::~HUD() {}

void HUD::initHUD() {
	if (!font.openFromFile("Assets/Fonts/Minecraft.ttf"))
		std::cerr << "error : load font minecraft" << std::endl;

	goldPiece.setTexture(&Shared::goldTexture);
	heart1.setTexture(&Shared::heart1Texture, true);
	heart2.setTexture(&Shared::heart2Texture, true);
	heart3.setTexture(&Shared::heart3Texture, true);

	gold.setString("0");
	gold.setCharacterSize({ 60 });
	gold.setOutlineThickness(5.f);
	gold.setOutlineColor(sf::Color::Black);
	gold.setFillColor(sf::Color::Yellow);
	gold.setPosition({ static_cast<float>(STGS::WIDTH * 0.05f), static_cast<float>(STGS::HEIGHT * 0.9f) });

	goldPiece.setSize({ STGS::WIDTH * 0.04f, STGS::WIDTH * 0.04f });
	goldPiece.setPosition({ gold.getPosition().x - goldPiece.getGlobalBounds().size.x, static_cast<float>(STGS::HEIGHT * 0.9f) });

	lifeholder.setSize({ STGS::WIDTH / 4.f, STGS::HEIGHT / 10.f + 75.f });
	lifeholder.setPosition({ static_cast<float>(STGS::WIDTH / 2.f - lifeholder.getSize().x / 2.f), 0 });

	timer.setString("Temps de la run : 0");
	timer.setCharacterSize({60});
	timer.setFillColor(sf::Color::White);
	timer.setOutlineThickness(5.f);
	timer.setOutlineColor(sf::Color::Black);
	timer.setPosition({ 10, 10 });

	score.setString("Score : 0");
	score.setCharacterSize(60);
	score.setFillColor(sf::Color::White);
	score.setOutlineThickness(5.f);
	score.setOutlineColor(sf::Color::Black);
	score.setPosition({ 10.f, timer.getGlobalBounds().size.y + timer.getPosition().y + 20.f });

	heart1.setSize({ lifeholder.getGlobalBounds().size.x / 3, lifeholder.getGlobalBounds().size.y - 50.f });
	heart1.setPosition({ lifeholder.getPosition().x, lifeholder.getPosition().y + 25.f });

	heart2.setSize({ lifeholder.getGlobalBounds().size.x / 3, lifeholder.getGlobalBounds().size.y - 50.f });
	heart2.setPosition({ lifeholder.getPosition().x + lifeholder.getGlobalBounds().size.x / 2 - heart2.getGlobalBounds().size.x / 2, lifeholder.getPosition().y + 25.f });

	heart3.setSize({ lifeholder.getGlobalBounds().size.x / 3, lifeholder.getGlobalBounds().size.y - 50.f });
	heart3.setPosition({ lifeholder.getPosition().x + lifeholder.getGlobalBounds().size.x - heart3.getGlobalBounds().size.x, lifeholder.getPosition().y + 25.f });
}

void HUD::drawHUD(sf::RenderWindow& window, Player& player) {
	window.draw(score);
	window.draw(timer);
	window.draw(lifeholder);
	window.draw(gold);
	window.draw(goldPiece);

	if (player.getLife() == 3) {
		window.draw(heart3);
		window.draw(heart2);
		window.draw(heart1);
	}
	else if (player.getLife() == 2) {
		window.draw(heart2);
		window.draw(heart1);
	}
	else if (player.getLife() == 1) {
		window.draw(heart1);
	}
}

void HUD::update(sf::Clock& clock, int& scoreGame, int& pessos) {
	sf::Time elapsed = clock.getElapsedTime();
	float seconds = elapsed.asSeconds();
	int roundedSeconds = std::round(seconds);
	timer.setString("Temps de la run : " + std::to_string(roundedSeconds));
	score.setString("Score : " + std::to_string(scoreGame));
	gold.setString(std::to_string(pessos));
}