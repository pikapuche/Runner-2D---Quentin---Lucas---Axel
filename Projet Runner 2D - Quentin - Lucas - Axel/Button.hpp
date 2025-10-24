#pragma once
#include "Map.hpp"

using namespace std;
using namespace sf;

class Button
{
public:
	Button();
	~Button();
	void activate();
	bool isHovering();

	enum ButtonState {
		NOTHING, PLAY, QUIT, SETTINGS
	};

	RectangleShape buttonBack;
	Text buttonText;
	Font buttonFont;
	String buttonTextContent;
	Texture buttonTexture;
};

