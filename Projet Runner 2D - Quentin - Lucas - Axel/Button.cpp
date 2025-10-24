#include "Button.hpp"
#include "Game.hpp"
#include <iostream>





Button::Button(sf::Vector2f spawnPosition, sf::Vector2f outlineSize, ButtonId buttonId, int zIndex)
{
	m_id = buttonId;

	m_position = spawnPosition;

	m_outline.setSize(outlineSize);
	m_outline.setOrigin(m_outline.getSize() / 2.f);
	m_outline.setFillColor(sf::Color::White);
	m_outline.setOutlineColor(sf::Color::Black);
	m_outline.setOutlineThickness(2.f);

	

	m_text.setFillColor(sf::Color::Black);
	m_text.setOrigin(m_outline.getOrigin());

	m_sprite.setOrigin(m_outline.getOrigin());

	m_zIndex = zIndex;
	m_isTransparent = false;

	m_savedOutlineSize = outlineSize;

	setupButton();
	

}

Button::Button(sf::Vector2f spawnPosition, sf::Vector2f outlineSize, ButtonId buttonId, std::string text, int zIndex)
{
	m_id = buttonId;

	m_position = spawnPosition;

	m_outline.setSize(outlineSize);
	m_outline.setOrigin(m_outline.getSize() / 2.f);
	m_outline.setFillColor(sf::Color::White);
	m_outline.setOutlineColor(sf::Color::Black);
	m_outline.setOutlineThickness(2.f);


	m_text.setFillColor(sf::Color::Black);
	m_text.setOrigin(m_outline.getOrigin());

	m_sprite.setOrigin(m_outline.getOrigin());

	m_zIndex = zIndex;
	m_isTransparent = false;

	m_savedOutlineSize = outlineSize;

	setupButton();
	
}

Button::~Button() {}

void Button::update(sf::RenderWindow& window, float deltaTime)
{
	static bool isMouseOverlapping = false;

	m_text.setPosition(m_position);
	m_outline.setPosition(m_position);

	//update sprite's size:
	sf::Vector2f outlineSize = m_outline.getSize();
	sf::Vector2u textureSize = m_texure.getSize();

	float scaleX = outlineSize.x / textureSize.x;
	float scaleY = outlineSize.y / textureSize.y;

	m_sprite.setScale(scaleX, scaleY);
	m_sprite.setOrigin(textureSize.x / 2.f, textureSize.y / 2.f);
	m_sprite.setPosition(m_position);

	//mouse overlap
	if (isMouseOverRectangle(m_outline, window)) isMouseOverlapping = true;
	else isMouseOverlapping = false;

	if (isMouseOverlapping)
	{
		m_outline.setSize({ m_savedOutlineSize.x + 20.f, m_savedOutlineSize.y + 20.f, });

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			activate(window, deltaTime, m_id);
		}
	}
	else
	{
		m_outline.setSize(m_savedOutlineSize);
	}
}


//void Button::draw(sf::RenderWindow& window)
//{
	//window.draw(m_sprite);
//}

void Button::setupButton()
{

	switch (m_id)
	{
	case NOTHING:
		m_text.setString("");
		;		break;
	case PLAY:
		loadTexture("../assets/uis/main_screen/PlayButton.png");
		isTransparent(true);
		break;
	case SETTINGS:
		loadTexture("../assets/uis/main_screen/SettingsButton.png");
		isTransparent(true);
		break;
	case QUIT:
		loadTexture("../assets/uis/main_screen/QuitButton.png");
		isTransparent(true);
		break;
	case SOUNDS_SETTINGS:
		loadTexture("../assets/uis/settings/SoundsButton.png");
		isTransparent(true);
		break;
	case CONTROLS:
		loadTexture("../assets/uis/settings/ControlsButton.png");
		isTransparent(true);
		break;
	case CREDITS:
		loadTexture("../assets/uis/settings/CreditsButton.png");
		isTransparent(true);
		break;
	case BACK:
		loadTexture("../assets/uis/BackButton.png");
		isTransparent(true);
		break;
	case PLUS:
		loadTexture("../assets/uis/settings/IncreaseSoundButton.png");
		isTransparent(true);
		break;
	case MINUS:
		loadTexture("../assets/uis/settings/DecreaseSoundButton.png");
		isTransparent(true);
		break;
	default:
		m_text.setString("");
		break;
	}
}

bool Button::isMouseOverRectangle(sf::RectangleShape& rect, const sf::RenderWindow& window)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	sf::Vector2f mousePosF = static_cast<sf::Vector2f>(mousePos);

	sf::Vector2f rectPos = rect.getPosition();
	sf::Vector2f rectSize = rect.getSize();


	//it's very poorly written but I didn't have the time to do something clean
	if (m_id == BACK)
	{
		float left = rectPos.x - rectSize.x / 2;
		float top = rectPos.y - rectSize.y / 2 + 30;
		float right = left + rectSize.x + 100;
		float bottom = top + rectSize.y;
		return mousePosF.x >= left && mousePosF.x <= right && mousePosF.y >= top && mousePosF.y <= bottom;
	}
	else if (m_id == MINUS)
	{
		float left = rectPos.x - rectSize.x / 2 + 350;
		float top = rectPos.y - rectSize.y / 2 + 30;
		float right = left + rectSize.x + 100;
		float bottom = top + rectSize.y;
		return mousePosF.x >= left && mousePosF.x <= right && mousePosF.y >= top && mousePosF.y <= bottom;
	}
	else if (m_id == PLUS)
	{
		float left = rectPos.x - rectSize.x / 2 + 600;
		float top = rectPos.y - rectSize.y / 2 + 30;
		float right = left + rectSize.x + 100;
		float bottom = top + rectSize.y;
		return mousePosF.x >= left && mousePosF.x <= right && mousePosF.y >= top && mousePosF.y <= bottom;
	}
	else
	{
		float left = rectPos.x - rectSize.x / 2 + 140;
		float top = rectPos.y - rectSize.y / 2 + 30;
		float right = left + rectSize.x + 230;
		float bottom = top + rectSize.y + 30;

		return mousePosF.x >= left && mousePosF.x <= right && mousePosF.y >= top && mousePosF.y <= bottom;
	}
}

void Button::activate(sf::RenderWindow& window, float deltaTime)
{
}

void Button::activate(sf::RenderWindow& window, float deltaTime, ButtonId id)
{


	

	switch (id)
	{
	case NOTHING:
		break;
	case PLAY:
		
		Game::PLAY;
		break;
	case SETTINGS:
		
		Game::SETTINGS;
		break;
	case QUIT:
		
		window.close();
		break;
	

	case CREDITS:
		
		Game::SETTINGS;
		break;

	default:
		break;
	}
}
