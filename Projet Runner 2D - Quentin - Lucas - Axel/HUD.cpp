#include "HUD.hpp"

HUD::HUD() : lvl(font),score(font), timer(font) {
	initTexture();
	initHUD();
}

HUD::~HUD() {

}


void HUD::initTexture() {
	if(!goldTexture.loadFromFile("Assets/Images/Gold.png"))
		cout << "cc";
	goldPiece.setTexture(&goldTexture);
}

void HUD::initHUD() {
	goldPiece.setPosition({ 50, static_cast<float>(STGS::HEIGHT - 100) });
	goldPiece.setSize({ 50,50 });
	lifeholder.setPosition({ static_cast<float>(STGS::WIDTH / 2), 200 });
	lifeholder.setSize({ 250,50 });
	lvl.setPosition({ static_cast<float>(STGS::WIDTH/2),static_cast<float>(STGS::HEIGHT/2) });
	score.setPosition({ 0,0 });
	timer.setPosition({ static_cast<float>(STGS::WIDTH-250), 0 });
	if (!heart1Texture.loadFromFile("Assets/Images/Heart_Live.png"));
	heart1.setPosition({ lifeholder.getPosition() });
	heart1.setSize({ 32, 32 });
	heart1.setTexture(&heart1Texture);
	if (!heart2Texture.loadFromFile("Assets/Images/hello_kitty_heart.png"));
	heart2.setPosition({ lifeholder.getPosition().x + 48, lifeholder.getPosition().y });
	heart2.setSize({ 32, 32 });
	heart2.setTexture(&heart2Texture);
	if (!heart3Texture.loadFromFile("Assets/Images/coeur_brise_de_mon_amour infini.png"));
	heart3.setPosition({ lifeholder.getPosition().x + 82, lifeholder.getPosition().y });
	heart3.setSize({ 32, 32 });
	heart3.setTexture(&heart3Texture);

	score.setString("C'est le score");
	lvl.setString("C'est le lvl");
	
	lvl.setCharacterSize({30});
	score.setCharacterSize({30});
	timer.setCharacterSize({30});

	lvl.setFillColor(Color::White);
	score.setFillColor(Color::White);
	timer.setFillColor(Color::White);

	font.openFromFile("Assets/Fonts/Minecraft.ttf");
}

void HUD::drawHUD(RenderWindow& window, Player& player) {
	window.draw(lvl);
	window.draw(score);
	window.draw(timer);
	window.draw(lifeholder);
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

void HUD::update(Clock& clock, int& scoreGame) {
	timer.setString(to_string(clock.getElapsedTime().asSeconds()));
	score.setString(to_string(scoreGame));
}