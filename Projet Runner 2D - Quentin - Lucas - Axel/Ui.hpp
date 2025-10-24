#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <thread>

class UI
{
public:
	UI();
	UI(sf::Vector2f spawnPosition, sf::Vector2f outlineSize, int zIndex, std::function<void()> behavior = []() {});
	UI(sf::Vector2f spawnPosition, sf::Vector2f outlineSize, std::string text, int zIndex, std::function<void()> behavior = []() {});
	virtual ~UI();

	virtual void			draw(sf::RenderWindow& window);
	virtual void			update(sf::RenderWindow& window, float deltaTime);	//called every frame
	void					runBehavior(std::function<void()> behavior); //runs the behavior in a thread so the ui could animate or do something else

	//GETTERS
	int						getZIndex() const;
	sf::Vector2f			getPosition() const;
	sf::RectangleShape& getOutline();
	sf::Text& getText();
	sf::Sprite& getSprite();

	//SETTERS
	void					setZIndex(int newZIndex);
	void					setPosition(sf::Vector2f newPosition);
	void					setOutlineSize(sf::Vector2f& newOutlineSize);
	void					setText(std::string& text);
	void					setSpriteColor(sf::Color newColor);


	void					loadTexture(std::string textureFilePath);
	void					isTransparent(bool boolValue);

	//OPERATOR OVERLOADS
	bool operator<(const UI& other) const;

protected:
	sf::Vector2f			m_position;
	int						m_zIndex; //Determines the layer the UI will be drawn on. An UI of index 2 will overlap an UI of index 1 for example.

	sf::RectangleShape		m_outline;
	sf::Sprite				m_sprite;
	sf::Texture				m_texure;

	sf::Text				m_text;
	sf::Font				m_font;

	bool					m_isTransparent;
};