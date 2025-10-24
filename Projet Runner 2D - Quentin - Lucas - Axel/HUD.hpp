#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Player.hpp"
#include "Map.hpp"

using namespace sf;
using namespace std;
using namespace STGS;
class HUD
{
public:
	HUD();
	
	~HUD();
	void initHUD();
	void drawHUD(RenderWindow& window, Player& player);
	void update(Clock& clock, int& score, int& pessos);
	void initTexture();
protected:

	Text timer;
	Text score;
	Text lvl;
	Text gold;
	Font font;
	RectangleShape lifeholder;
	RectangleShape heart1;
	RectangleShape heart2;
	RectangleShape heart3;
	Texture heart1Texture;
	Texture heart2Texture;
	Texture heart3Texture;
	Map map;
	RectangleShape goldPiece;
	Texture goldTexture;

};

