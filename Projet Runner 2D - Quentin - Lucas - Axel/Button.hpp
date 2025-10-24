#pragma once
#include <SFML/Graphics.hpp>
#include "Ui.hpp"

enum ButtonId
{
	NOTHING = 0, PLAY, SETTINGS, QUIT, SOUNDS_SETTINGS, CONTROLS, CREDITS, BACK, PLUS, MINUS
};

class Button : public UI
{
public:

	Button(sf::Vector2f spawnPosition, sf::Vector2f outlineSize, ButtonId buttonId, int zIndex);
	Button(sf::Vector2f spawnPosition, sf::Vector2f outlineSize, ButtonId buttonId, std::string text, int zIndex);
	~Button();

	void update(sf::RenderWindow& window, float deltaTime) override;

	//GETTERS
	ButtonId getId() const { return m_id; }

private:

	void setupButton();
	bool isMouseOverRectangle(sf::RectangleShape& rect, const sf::RenderWindow& window);

	void activate(sf::RenderWindow& window, float deltaTime); //activate when button is pressed
	void activate(sf::RenderWindow& window, float deltaTime, ButtonId id); //activate when button is pressed

private:

	ButtonId m_id;
	sf::Vector2f m_savedOutlineSize; 
};