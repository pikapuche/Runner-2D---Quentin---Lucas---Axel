#include "UI.hpp"
#include <iostream>

UI::UI()
{
	m_position = { 0, 0 };

	m_outline.setSize({ 100, 100 });
	m_outline.setOrigin(m_outline.getSize() / 2.f);
	m_outline.setFillColor(sf::Color::White);
	m_outline.setOutlineColor(sf::Color::Black);
	m_outline.setOutlineThickness(2.f);

	if (m_font.loadFromFile("../assets/MGS2.ttf")) { m_text.setFont(m_font); m_text.setString(""); }

	m_text.setOrigin(m_outline.getOrigin());

	m_sprite.setOrigin(m_outline.getOrigin());

	m_zIndex = 0;
	m_isTransparent = false;
}

UI::UI(sf::Vector2f spawnPosition, sf::Vector2f outlineSize, int zIndex, std::function<void()> behavior)
{
	m_position = spawnPosition;

	m_outline.setSize(outlineSize);
	m_outline.setOrigin(m_outline.getSize() / 2.f);
	m_outline.setFillColor(sf::Color::White);
	m_outline.setOutlineColor(sf::Color::Black);
	m_outline.setOutlineThickness(2.f);

	if (m_font.loadFromFile("../assets/MGS2.ttf")) { m_text.setFont(m_font); m_text.setString(""); }

	m_text.setOrigin(m_outline.getOrigin());

	m_sprite.setOrigin(m_outline.getOrigin());

	m_zIndex = zIndex;
	m_isTransparent = false;

	runBehavior(behavior);
}

UI::UI(sf::Vector2f spawnPosition, sf::Vector2f outlineSize, std::string text, int zIndex, std::function<void()> behavior)
{
	m_position = spawnPosition;

	m_outline.setSize(outlineSize);
	m_outline.setOrigin(m_outline.getSize() / 2.f);
	m_outline.setFillColor(sf::Color::White);
	m_outline.setOutlineColor(sf::Color::Black);
	m_outline.setOutlineThickness(2.f);

	if (m_font.loadFromFile("../assets/MGS2.ttf")) { m_text.setFont(m_font); m_text.setString(text); }

	m_text.setFillColor(sf::Color::Black);
	m_text.setOrigin(m_outline.getOrigin());

	m_sprite.setOrigin(m_outline.getOrigin());

	m_zIndex = zIndex;
	m_isTransparent = false;

	runBehavior(behavior);
}

UI::~UI()
{
}

void UI::draw(sf::RenderWindow& window)
{
	if (m_isTransparent) { m_outline.setFillColor(sf::Color::Transparent); m_outline.setOutlineColor(sf::Color::Transparent); }
	window.draw(m_outline);
	window.draw(m_sprite);
	window.draw(m_text);
}

void UI::update(sf::RenderWindow& window, float deltaTime)
{
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
	//use this to animate uis
}

void UI::runBehavior(std::function<void()> behavior)
{
	std::thread t(behavior);
	t.detach();
}

//GETTERS///////////////////////////////////////////////////////////////
int						UI::getZIndex() const { return m_zIndex; }
sf::Vector2f			UI::getPosition() const { return m_position; }
sf::RectangleShape& UI::getOutline() { return m_outline; }
sf::Text& UI::getText() { return m_text; }
sf::Sprite& UI::getSprite() { return m_sprite; }
////////////////////////////////////////////////////////////////////////


//SETTERS//////////////////////////////////////////////////////////////////////////////////////////////////////
void					UI::setZIndex(int newZIndex) { m_zIndex = newZIndex; }
void					UI::setPosition(sf::Vector2f newPosition) { m_position = newPosition; }
void					UI::setOutlineSize(sf::Vector2f& newOutlineSize) { m_outline.setSize(newOutlineSize); }
void					UI::setText(std::string& text) { m_text.setString(text); }
void					UI::setSpriteColor(sf::Color newColor) { m_sprite.setColor(newColor); }
//void					UI::setSprite(sf::Sprite& newSprite) { m_sprite = newSprite; }
void					UI::isTransparent(bool boolValue) { m_isTransparent = boolValue; }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void UI::loadTexture(std::string textureFilePath)
{
	if (!m_texure.loadFromFile(textureFilePath))
	{
		std::cout << "Couldn't load the UI texture!\n";
	}
	m_sprite.setTexture(m_texure);
}



//OPERATOR OVERLOADS
bool UI::operator<(const UI& other) const
{
	return m_zIndex < other.getZIndex();
}