#include "Shop.hpp"

Shop::Shop() : font("Assets/Fonts/Minecraft.ttf"), shop(font) {
	shopBackgroundShape.setSize(sf::Vector2f(static_cast<float>(STGS::WIDTH), static_cast<float>(STGS::HEIGHT)));
	shopBackgroundShape.setPosition({ 0, 0 });
	shopBackgroundShape.setTexture(&Shared::backboardFirstTextureDifficultyTwo);

	shopCaseOneShape.setSize({ static_cast<float>(STGS::WIDTH / 3) - static_cast<float>(STGS::GAP_X), static_cast<float>(STGS::HEIGHT) * 2 / 3 - static_cast<float>(STGS::GAP_Y) });
	shopCaseOneShape.setPosition({ static_cast<float>(STGS::GAP_X / 3), static_cast<float>(STGS::HEIGHT) * 1 / 3 });
	shopCaseOneShape.setFillColor(sf::Color::Green);

	shopCaseTwoShape.setSize({ static_cast<float>(STGS::WIDTH / 3) - static_cast<float>(STGS::GAP_X), static_cast<float>(STGS::HEIGHT) * 2 / 3 - static_cast<float>(STGS::GAP_Y) });
	shopCaseTwoShape.setPosition({ static_cast<float>(STGS::WIDTH * 1 / 3 + STGS::GAP_X * 1 / 3), static_cast<float>(STGS::HEIGHT * 1 / 3) });
	shopCaseTwoShape.setFillColor(sf::Color::Green);

	shopCaseThreeShape.setSize({ static_cast<float>(STGS::WIDTH / 3) - static_cast<float>(STGS::GAP_X), static_cast<float>(STGS::HEIGHT) * 2 / 3 - static_cast<float>(STGS::GAP_Y) });
	shopCaseThreeShape.setPosition({ static_cast<float>(STGS::WIDTH * 2 / 3 + STGS::GAP_X * 2 / 3), static_cast<float>(STGS::HEIGHT * 1 / 3) });
	shopCaseThreeShape.setFillColor(sf::Color::Green);

	shop.setString("SHOP");
	shop.setCharacterSize(300);
	shop.setPosition({ static_cast<float>(STGS::GAP_X), static_cast<float>(STGS::HEIGHT * 0.01f) });

	shopVictoryShape.setSize({ static_cast<float>(STGS::WIDTH / 3) - static_cast<float>(STGS::GAP_X), static_cast<float>(STGS::HEIGHT) * 1 / 3 - static_cast<float>(STGS::GAP_Y) });
	shopVictoryShape.setPosition({ static_cast<float>(STGS::WIDTH * 2 / 3 + STGS::GAP_X * 2 / 3), static_cast<float>(STGS::HEIGHT * 0.01f) });
	shopVictoryShape.setFillColor(sf::Color::Magenta);
}

Shop::~Shop() {}

void Shop::update() {

}

void Shop::render(sf::RenderWindow& window) {
	window.draw(shopBackgroundShape);
	window.draw(shopCaseOneShape);
	window.draw(shopCaseTwoShape);
	window.draw(shopCaseThreeShape);
	window.draw(shop);
	window.draw(shopVictoryShape);
}