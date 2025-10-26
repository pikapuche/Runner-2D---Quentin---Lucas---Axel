#include "HUD.hpp"

HUD::HUD() : lvl(font),score(font), timer(font), gold(font) {
	initHUD();
}

HUD::~HUD() {}

void HUD::initHUD() {
	if (!font.openFromFile("Assets/Fonts/Minecraft.ttf"))
		std::cerr << "error : load font minecraft" << std::endl;

	goldPiece.setTexture(&Shared::goldTexture);
	heart1.setTexture(&Shared::heart1Texture, true);
	heart2.setTexture(&Shared::heart2Texture, true);
	heart3.setTexture(&Shared::heart3Texture, true);

	goldPiece.setPosition({ 50, static_cast<float>(STGS::HEIGHT - 100) });
	goldPiece.setSize({ 50,50 });

	lifeholder.setPosition({ static_cast<float>(STGS::WIDTH / 2), 200 });
	lifeholder.setSize({ 250,50 });

	lvl.setPosition({ static_cast<float>(STGS::WIDTH/2),static_cast<float>(STGS::HEIGHT/2) });
	lvl.setString("C'est le lvl");
	lvl.setCharacterSize({30});
	lvl.setFillColor(sf::Color::White);

	score.setPosition({ 0,0 });
	score.setString("C'est le score");
	score.setCharacterSize({30});
	score.setFillColor(sf::Color::White);

	timer.setPosition({ static_cast<float>(STGS::WIDTH-250), 0 });
	timer.setCharacterSize({30});
	timer.setFillColor(sf::Color::White);

	gold.setPosition({ static_cast<float>(STGS::WIDTH), static_cast<float>(STGS::HEIGHT - 100) });
	gold.setCharacterSize({ 30 });
	gold.setFillColor(sf::Color::Yellow);

	heart1.setPosition({ lifeholder.getPosition() });
	heart1.setSize({ 32, 32 });

	heart2.setPosition({ lifeholder.getPosition().x + 48, lifeholder.getPosition().y });
	heart2.setSize({ 32, 32 });

	heart3.setPosition({ lifeholder.getPosition().x + 82, lifeholder.getPosition().y });
	heart3.setSize({ 32, 32 });
}

void HUD::drawHUD(sf::RenderWindow& window, Player& player) {
	window.draw(lvl);
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
	timer.setString(std::to_string(clock.getElapsedTime().asSeconds()));
	score.setString(std::to_string(scoreGame));
	gold.setString(std::to_string(pessos));
}