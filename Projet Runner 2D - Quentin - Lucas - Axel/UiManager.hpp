#pragma once
#include "UI.hpp"
#include "Button.hpp"
#include <vector>
#include <algorithm>

using SharedPtrUIVector_t = std::vector<std::shared_ptr<UI>>;
using SharedPtrButtonVector_t = std::vector<std::shared_ptr<Button>>;

class UiManager
{
public:

	void						drawScreen(sf::RenderWindow& window, float deltaTime);
	void						updateScreen(sf::RenderWindow& window, float deltaTime);

	//GETTERS
	SharedPtrButtonVector_t& getButtons();
	SharedPtrUIVector_t& getBackgrounds();
	std::shared_ptr<UI>			getSettingsSubMenu();
	sf::View& getUIView();

	//ADD REMOVE
	std::weak_ptr<UI>			addUI(std::shared_ptr<UI> uiSharedPtr); //adds an ui and puts it in the m_backgrounds vector
	std::weak_ptr<Button>		addButton(std::shared_ptr<Button> buttonSharedPtr); //adds an ui and puts it in the m_buttons vector

	void						removeUI(std::shared_ptr<UI> uiSharedPtr); //removes the ui from both m_allUis and m_backgrounds/m_buttons vectors
	void						removeUI(std::weak_ptr<UI> uiWeakPtr); //You can remove an UI from the m_uis vector with a weak_ptr

	void						setSettingsSubMenu(std::shared_ptr<UI> uiSharedPtr);

	std::shared_ptr<UI>			getSettingsSubMenu(std::shared_ptr<UI> uiSharedPtr);

	void						clearAllUIs();

private:
	SharedPtrButtonVector_t	m_buttons;
	SharedPtrUIVector_t		m_backgrounds;

	SharedPtrUIVector_t		m_allUis; //only used to draw the full screen (using the zindex values of everything)

	std::shared_ptr<UI>		m_settingsSubMenu; //Menu shown in the settings menu

	sf::View				m_uiView; //the view is used to lock ui elements in a fixed space (unlike entities that move continuously)
};