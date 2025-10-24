#pragma once
#include <iostream>
#include "Button.hpp"
#include "Ui.hpp"

using SharedPtrUIVector_t = std::vector<std::shared_ptr<UI>>;
using SharedPtrButtonVector_t = std::vector<std::shared_ptr<Button>>;

class MenuStart
{
public:
	MenuStart();
	~MenuStart();

	void initMenu();
	void drawButtons(sf::RenderWindow& window);
	void drawUis(sf::RenderWindow& window);
	void drawAll(sf::RenderWindow& window);
private:
	Button play;
	Button quit;
	Button settings;

	SharedPtrButtonVector_t	m_buttons;
	SharedPtrUIVector_t		m_allUis;


};

