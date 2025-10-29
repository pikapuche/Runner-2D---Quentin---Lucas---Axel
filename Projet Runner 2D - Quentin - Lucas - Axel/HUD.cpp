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

	timer.setString("Temps de la run : 0");
	timer.setCharacterSize({60});
	timer.setFillColor(sf::Color::White);
	timer.setOutlineThickness(5.f);
	timer.setOutlineColor(sf::Color::Black);
	timer.setPosition({ static_cast<float>(STGS::WIDTH * 0.01), static_cast<float>(STGS::HEIGHT * 0.01) });

	score.setString("Score : 0");
	score.setCharacterSize(60);
	score.setFillColor(sf::Color::White);
	score.setOutlineThickness(5.f);
	score.setOutlineColor(sf::Color::Black);
	score.setPosition({ static_cast<float>(STGS::WIDTH) - score.getGlobalBounds().size.x - static_cast<float>(STGS::WIDTH * 0.01), static_cast<float>(STGS::HEIGHT * 0.f)});

	heart1.setSize({ static_cast<float>(STGS::WIDTH * 0.05), static_cast<float>(STGS::HEIGHT * 0.07) });
	heart1.setPosition({ static_cast<float>(STGS::WIDTH * 0.01), timer.getPosition().y + timer.getGlobalBounds().size.y + static_cast<float>(STGS::HEIGHT * 0.03) });

	heart2.setSize({ static_cast<float>(STGS::WIDTH * 0.05), static_cast<float>(STGS::HEIGHT * 0.07) });
	heart2.setPosition({ heart1.getPosition().x + heart1.getGlobalBounds().size.x + static_cast<float>(STGS::WIDTH * 0.01), timer.getPosition().y + timer.getGlobalBounds().size.y + static_cast<float>(STGS::HEIGHT * 0.02) });
	heart2.setScale({ 1.5, 1.5 });

	heart3.setSize({ static_cast<float>(STGS::WIDTH * 0.05), static_cast<float>(STGS::HEIGHT * 0.07) });
	heart3.setPosition({ heart2.getPosition().x + heart2.getGlobalBounds().size.x + static_cast<float>(STGS::WIDTH * 0.001), timer.getPosition().y + timer.getGlobalBounds().size.y + static_cast<float>(STGS::HEIGHT * 0.03) });
}

void HUD::drawHUD(sf::RenderWindow& window, Player& player) {
	window.draw(score);
	window.draw(timer);
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
	elapsed = clock.getElapsedTime();
	seconds = elapsed.asSeconds();
	sbstr = 4;
	if (seconds >= 10)
		sbstr = 5;
	else if (seconds >= 100)
		sbstr = 6;
	timer.setString("Timer : " + std::to_string(seconds).substr(0, sbstr));
	score.setString("Score : " + std::to_string(scoreGame));
	gold.setString(std::to_string(pessos));
}