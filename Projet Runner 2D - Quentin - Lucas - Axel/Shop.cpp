#include "Shop.hpp"

Shop::Shop() : font("Assets/Fonts/Minecraft.ttf"), shopText(font), skin1Text(font), skin2Text(font), skin3Text(font), victoryText(font), goldText(font), popupText(font) {

	shopClock.restart();
	gapX = 60.f;
	gapY = 60.f;

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

	shopText.setString("SHOP");
	shopText.setCharacterSize(300);
	shopText.setPosition({ static_cast<float>(STGS::GAP_X), static_cast<float>(STGS::HEIGHT * 0.01f) });

	shopVictoryShape.setSize({ static_cast<float>(STGS::WIDTH / 3) - static_cast<float>(STGS::GAP_X), static_cast<float>(STGS::HEIGHT) * 1 / 3 - static_cast<float>(STGS::GAP_Y) });
	shopVictoryShape.setPosition({ static_cast<float>(STGS::WIDTH * 2 / 3 + STGS::GAP_X * 2 / 3), static_cast<float>(STGS::HEIGHT * 0.01f) });
	shopVictoryShape.setFillColor(sf::Color::Green);

	coin1.setSize({ 50, 50 });
	coin1.setPosition({ 20, 20 });
	coin1.setTexture(&Shared::goldTexture);

	coin2.setSize({ 50, 50 });
	coin2.setPosition({ shopCaseOneShape.getPosition().x + 10.f, shopCaseOneShape.getPosition().y + shopCaseOneShape.getGlobalBounds().size.y - coin2.getGlobalBounds().size.y - 20.f});
	coin2.setTexture(&Shared::goldTexture);

	coin3.setSize({ 50, 50 });
	coin3.setPosition({ shopCaseTwoShape.getPosition().x + 10.f, shopCaseTwoShape.getPosition().y + shopCaseTwoShape.getGlobalBounds().size.y - coin3.getGlobalBounds().size.y - 20.f });
	coin3.setTexture(&Shared::goldTexture);

	coin4.setSize({ 50, 50 });
	coin4.setPosition({ shopCaseThreeShape.getPosition().x + 10.f, shopCaseThreeShape.getPosition().y + shopCaseThreeShape.getGlobalBounds().size.y - coin4.getGlobalBounds().size.y - 20.f });
	coin4.setTexture(&Shared::goldTexture);

	coin5.setSize({ 50, 50 });
	coin5.setPosition({ shopVictoryShape.getPosition().x + 10.f, shopVictoryShape.getPosition().y + shopVictoryShape.getGlobalBounds().size.y - coin5.getGlobalBounds().size.y - 10.f });
	coin5.setTexture(&Shared::goldTexture);

	rect1.setSize({ shopCaseOneShape.getGlobalBounds().size.x - gapX, shopCaseOneShape.getGlobalBounds().size.y - gapY * 2 });
	rect1.setPosition({ shopCaseOneShape.getPosition().x + gapX / 2, shopCaseOneShape.getPosition().y + gapY / 2 });

	rect2.setSize({ shopCaseTwoShape.getGlobalBounds().size.x - gapX, shopCaseTwoShape.getGlobalBounds().size.y - gapY * 2 });
	rect2.setPosition({ shopCaseTwoShape.getPosition().x + gapX / 2, shopCaseTwoShape.getPosition().y + gapY / 2 });

	rect3.setSize({ shopCaseThreeShape.getGlobalBounds().size.x - gapX, shopCaseThreeShape.getGlobalBounds().size.y - gapY * 2 });
	rect3.setPosition({ shopCaseThreeShape.getPosition().x + gapX / 2, shopCaseThreeShape.getPosition().y + gapY / 2 });

	rect4.setSize({ shopVictoryShape.getGlobalBounds().size.x - gapX, shopVictoryShape.getGlobalBounds().size.y - gapY * 2 });
	rect4.setPosition({ shopVictoryShape.getPosition().x + gapX / 2, shopVictoryShape.getPosition().y + gapY / 2 });

	skin1Text.setString("10 - Skin 1 bb");
	skin1Text.setCharacterSize(50);
	skin1Text.setPosition({ coin2.getPosition().x + coin2.getGlobalBounds().size.x, coin2.getPosition().y });

	skin2Text.setString("15 - Skin 2 bb");
	skin2Text.setCharacterSize(50);
	skin2Text.setPosition({ coin3.getPosition().x + coin3.getGlobalBounds().size.x, coin3.getPosition().y });

	skin3Text.setString("20 - Skin 3 bb");
	skin3Text.setCharacterSize(50);
	skin3Text.setPosition({ coin4.getPosition().x + coin4.getGlobalBounds().size.x, coin4.getPosition().y });

	victoryText.setString("50 - Victoire");
	victoryText.setCharacterSize(50);
	victoryText.setPosition({ coin5.getPosition().x + coin5.getGlobalBounds().size.x, coin5.getPosition().y });

	goldText.setString("0");
	goldText.setCharacterSize(50);
	goldText.setPosition({ coin1.getPosition().x + coin1.getGlobalBounds().size.x, coin1.getPosition().y});

	skinOneShape.setSize({ rect1.getGlobalBounds().size.x - gapX, rect1.getGlobalBounds().size.y - gapY });
	skinOneShape.setPosition({ rect1.getPosition().x + gapX / 2, rect1.getPosition().y + gapY / 2 });
	skinOneShape.setTexture(&Shared::playerTexture);
	skinOneShape.setFillColor(sf::Color::Green);

	skinTwoShape.setSize({ rect2.getGlobalBounds().size.x - gapX, rect2.getGlobalBounds().size.y - gapY });
	skinTwoShape.setPosition({ rect2.getPosition().x + gapX / 2, rect2.getPosition().y + gapY / 2 });
	skinTwoShape.setTexture(&Shared::playerTexture);
	skinTwoShape.setFillColor(sf::Color::Magenta);

	skinThreeShape.setSize({ rect3.getGlobalBounds().size.x - gapX, rect3.getGlobalBounds().size.y - gapY });
	skinThreeShape.setPosition({ rect3.getPosition().x + gapX / 2, rect3.getPosition().y + gapY / 2 });
	skinThreeShape.setTexture(&Shared::playerTexture);
	skinThreeShape.setFillColor(sf::Color::Yellow);

	popupBox.setSize({ 600, 200 });
	popupBox.setFillColor(sf::Color(0, 0, 0, 200));
	popupBox.setOutlineThickness(3);
	popupBox.setOutlineColor(sf::Color::White);
	popupBox.setOrigin(popupBox.getSize() / 2.f);
	popupBox.setPosition({ static_cast<float>(STGS::WIDTH / 2.f), static_cast<float>(STGS::HEIGHT / 2.f) });

	popupText.setFont(font);
	popupText.setCharacterSize(40);
	popupText.setFillColor(sf::Color::White);
}

Shop::~Shop() {}

void Shop::update(int& gold) {
	std::string tempString = std::to_string(gold);
	goldText.setString(tempString);

	sf::Vector2f mousePos = { static_cast<float>(sf::Mouse::getPosition().x), static_cast<float>(sf::Mouse::getPosition().y) };

	// --- Cases ---
	auto handleHover = [&](sf::RectangleShape& shape) {
		if (shape.getGlobalBounds().contains(mousePos)) 
			shape.setFillColor(sf::Color::Cyan);
		else 
			shape.setFillColor(sf::Color::Green);
		};

	handleHover(shopCaseOneShape);
	handleHover(shopCaseTwoShape);
	handleHover(shopCaseThreeShape);
	handleHover(shopVictoryShape);

	buying(gold);
	if (showPopup && popupClock.getElapsedTime().asSeconds() > 2.f) {
		showPopup = false;
	}
}


void Shop::render(sf::RenderWindow& window) {
	window.draw(shopBackgroundShape);
	window.draw(shopCaseOneShape);
	window.draw(shopCaseTwoShape);
	window.draw(shopCaseThreeShape);
	window.draw(shopText);
	window.draw(shopVictoryShape);
	window.draw(coin1);
	window.draw(coin2);
	window.draw(coin3);
	window.draw(coin4);
	window.draw(coin5);
	window.draw(rect1);
	window.draw(rect2);
	window.draw(rect3);
	window.draw(rect4);
	window.draw(skin1Text);
	window.draw(skin2Text);
	window.draw(skin3Text);
	window.draw(victoryText);
	window.draw(goldText);
	window.draw(skinOneShape);
	window.draw(skinTwoShape);
	window.draw(skinThreeShape);
	if (showPopup) {
		window.draw(popupBox);
		window.draw(popupText);
	}
}

void Shop::buying(int& gold) {
	sf::Vector2f mousePos = { static_cast<float>(sf::Mouse::getPosition().x), static_cast<float>(sf::Mouse::getPosition().y) };

	// --- Donn�es d'achat ---
	const int priceSkin1 = 10;
	const int priceSkin2 = 15;
	const int priceSkin3 = 20;
	const int priceVictory = 50;

	// --- Achat des skins ---
	auto tryBuySkin = [&](sf::RectangleShape& shape, int price, bool& skinBool, const std::string& skinName) {
		if (shape.getGlobalBounds().contains(mousePos) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && shopClock.getElapsedTime().asSeconds() > 1.f) {
			if (gold >= price) {
				gold -= price;
				skin1Bool = false;
				skin2Bool = false;
				skin3Bool = false;
				skinBool = true;

				showMessage("Vous avez achet� et �quip� " + skinName + " !");

				shopClock.restart();
			}
			else {
				showMessage("Pas assez de gold pour acheter le " + skinName + " !");

				shopClock.restart();
			}
		}
		};

	tryBuySkin(shopCaseOneShape, priceSkin1, skin1Bool, "Skin 1");
	tryBuySkin(shopCaseTwoShape, priceSkin2, skin2Bool, "Skin 2");
	tryBuySkin(shopCaseThreeShape, priceSkin3, skin3Bool, "Skin 3");

	// --- Achat de la victoire ---
	if (shopVictoryShape.getGlobalBounds().contains(mousePos) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && shopClock.getElapsedTime().asSeconds() > 1.f) {
		if (gold >= priceVictory) {
			gold -= priceVictory;
			std::cout << "Victoire achet�e !" << std::endl;
			victoryUnlocked = true;
			shopClock.restart();
		}
		else {
			std::cout << "Pas assez de gold pour acheter la victoire." << std::endl;
			shopClock.restart();
		}
	}
}

int Shop::getSkin() {
	if (skin1Bool)
		return 1;
	else if (skin2Bool)
		return 2;
	else if (skin3Bool)
		return 3;
	return 0;
}

void Shop::showMessage(const std::string& message) {
	popupMessage = message;
	popupText.setString(popupMessage);
	popupText.setPosition({ popupBox.getPosition().x - popupText.getGlobalBounds().size.x / 2,
		popupBox.getPosition().y - popupText.getGlobalBounds().size.y / 2 });
	popupClock.restart();
	showPopup = true;
}