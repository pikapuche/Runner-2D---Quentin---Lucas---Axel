#include "UiManager.h"
#include "Button.h"
#include <iostream>


void UiManager::drawScreen(sf::RenderWindow& window, float deltaTime)
{
	if (m_allUis.empty()) return;
	//std::cout << "DRAWING GUIS\n";
	std::stable_sort(m_allUis.begin(), m_allUis.end(), [](const std::shared_ptr<UI>& a, const std::shared_ptr<UI>& b) {
		return a->getZIndex() < b->getZIndex();
		});
	for (auto& ui : m_allUis)
	{
		if (!ui) continue;
		ui->draw(window);
	}
	if (m_settingsSubMenu) m_settingsSubMenu->draw(window);
}

void UiManager::updateScreen(sf::RenderWindow& window, float deltaTime)
{
	if (m_allUis.empty()) return;
	for (auto& ui : m_allUis)
	{
		if (!ui) continue;
		ui->update(window, deltaTime);
	}
}

//GETTERS///////////////////////////////////////////////////////////////////
SharedPtrButtonVector_t& UiManager::getButtons() { return m_buttons; }
SharedPtrUIVector_t& UiManager::getBackgrounds() { return m_backgrounds; }
std::shared_ptr<UI>		 UiManager::getSettingsSubMenu() { return m_settingsSubMenu; }
sf::View& UiManager::getUIView() { return m_uiView; }
////////////////////////////////////////////////////////////////////////////

std::weak_ptr<UI> UiManager::addUI(std::shared_ptr<UI> uiSharedPtr)
{
	m_allUis.push_back(uiSharedPtr);
	m_backgrounds.push_back(uiSharedPtr);

	return uiSharedPtr;
}

std::weak_ptr<Button> UiManager::addButton(std::shared_ptr<Button> buttonSharedPtr)
{
	auto button = std::dynamic_pointer_cast<UI>(buttonSharedPtr);
	m_allUis.push_back(button);
	m_buttons.push_back(buttonSharedPtr);
	return buttonSharedPtr;
}

void UiManager::removeUI(std::shared_ptr<UI> uiSharedPtr)
{
	//Deletes the ui from the global vector
	auto iterator = std::find(m_allUis.begin(), m_allUis.end(), uiSharedPtr);
	if (iterator != m_allUis.end())
	{
		iterator->reset();
	}

	//Deletes the ui from their respective vector
	if (auto ui = std::dynamic_pointer_cast<Button>(uiSharedPtr))
	{
		auto buttonIterator = std::find(m_buttons.begin(), m_buttons.end(), uiSharedPtr);
		if (buttonIterator != m_buttons.end())
		{
			buttonIterator->reset();
		}
	}
	else
	{
		auto backgroundIterator = std::find(m_backgrounds.begin(), m_backgrounds.end(), uiSharedPtr);
		if (backgroundIterator != m_backgrounds.end())
		{
			backgroundIterator->reset();
		}
	}

}

void UiManager::removeUI(std::weak_ptr<UI> uiWeakPtr)
{
	//Deletes the ui from the global vector
	auto uiSharedPtr = uiWeakPtr.lock();

	if (uiSharedPtr)
	{
		auto iterator = std::find(m_allUis.begin(), m_allUis.end(), uiSharedPtr);
		if (iterator != m_allUis.end())
		{
			iterator->reset();
		}
	}

	//Deletes the ui from their respective vector
	if (auto ui = std::dynamic_pointer_cast<Button>(uiSharedPtr))
	{
		auto buttonIterator = std::find(m_buttons.begin(), m_buttons.end(), uiSharedPtr);
		if (buttonIterator != m_buttons.end())
		{
			buttonIterator->reset();
		}
	}
	else
	{
		auto backgroundIterator = std::find(m_backgrounds.begin(), m_backgrounds.end(), uiSharedPtr);
		if (backgroundIterator != m_backgrounds.end())
		{
			backgroundIterator->reset();
		}
	}
}

void UiManager::setSettingsSubMenu(std::shared_ptr<UI> uiSharedkPtr)
{
	if (m_settingsSubMenu)
	{
		auto it = std::remove(m_allUis.begin(), m_allUis.end(), m_settingsSubMenu);
		if (it != m_allUis.end()) m_allUis.erase(it, m_allUis.end());

		auto it2 = std::remove(m_backgrounds.begin(), m_backgrounds.end(), m_settingsSubMenu);
		if (it2 != m_backgrounds.end()) m_backgrounds.erase(it2, m_backgrounds.end());

		for (auto& button : m_buttons)
		{
			if (!button) continue;
			if (button->getId() == ButtonId::PLUS || button->getId() == ButtonId::MINUS)
			{
				auto it = std::remove(m_allUis.begin(), m_allUis.end(), button);
				if (it != m_allUis.end()) m_allUis.erase(it, m_allUis.end());

				button.reset();
			}
		}

		m_settingsSubMenu.reset();
	}

	m_settingsSubMenu = uiSharedkPtr;

	if (std::find(m_allUis.begin(), m_allUis.end(), m_settingsSubMenu) == m_allUis.end()) {
		m_allUis.push_back(m_settingsSubMenu);
	}
}

std::shared_ptr<UI> UiManager::getSettingsSubMenu(std::shared_ptr<UI> uiSharedPtr)
{
	return m_settingsSubMenu;
}

void UiManager::clearAllUIs()
{
	for (auto& ui : m_allUis)
	{
		ui.reset();
	}
	for (auto& ui : m_buttons)
	{
		ui.reset();
	}
	for (auto& ui : m_backgrounds)
	{
		ui.reset();
	}
	m_allUis.clear();
	m_settingsSubMenu.reset();
}
