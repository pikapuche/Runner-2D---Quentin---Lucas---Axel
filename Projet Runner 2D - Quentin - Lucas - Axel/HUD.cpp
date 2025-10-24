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
	lifeholder.setPosition({ static_cast<float>(STGS::WIDTH / 2), 0 });
	lifeholder.setSize({ 250,50 });
	lvl.setPosition({ static_cast<float>(STGS::WIDTH/2),static_cast<float>(STGS::HEIGHT/2) });
	score.setPosition({ 0,0 });
	timer.setPosition({ static_cast<float>(STGS::WIDTH-250), 0 });

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

void HUD::drawHUD(RenderWindow& window) {
	window.draw(lvl);
	window.draw(score);
	window.draw(timer);
	window.draw(lifeholder);
	window.draw(goldPiece);
	

}
void HUD::calculateTimer(Clock& clock) {
	
}
void HUD::update(Clock& clock, int& scoreGame) {
	timer.setString(to_string(clock.getElapsedTime().asSeconds()));
	score.setString(to_string(scoreGame));
}