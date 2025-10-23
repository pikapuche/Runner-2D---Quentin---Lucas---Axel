#include "HUD.hpp"




HUD::HUD() : lvl(font),score(font), timer(font) {
	initHUD();
}

HUD::~HUD() {

}

void HUD::initHUD() {
	lifeholder.setPosition({ STGS::WIDTH / 2, 0 });
	lifeholder.setSize({ 250,50 });
	lvl.setPosition({ STGS::WIDTH/2,STGS::HEIGHT/2 });
	score.setPosition({ 0,0 });
	timer.setPosition({ STGS::WIDTH-250, 0 });
	
	score.setString("C'est le score");
	lvl.setString("C'est le lvl");
	
	lvl.setCharacterSize({ 30});
	score.setCharacterSize({ 30});
	timer.setCharacterSize({ 30});

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
	cout << "tout est draw hihihih";
	

}
void HUD::calculateTimer(Clock& clock) {
	
}
void HUD::update(Clock& clock) {
	timer.setString(to_string(clock.getElapsedTime().asSeconds()));
}