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
	void drawHUD(RenderWindow& window);
	void update(Clock& clock);
	void calculateTimer(Clock& clock);
	void initTexture();
protected:

	Text timer;
	Text score;
	Text lvl;
	Font font;
	RectangleShape lifeholder;
	RectangleShape heart1;
	RectangleShape heart2;
	RectangleShape heart3;
	Map map;
	RectangleShape goldPiece;
	Texture goldTexture;
};

