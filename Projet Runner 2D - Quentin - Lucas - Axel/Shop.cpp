#include "Shop.hpp"

Shop::Shop() : font("Assets/Fonts/Minecraft.ttf"), shopText(font), skin1Text(font), skin2Text(font), skin3Text(font), victoryText(font), goldText(font), popupText(font), shop2Text(font) {
	gapX = 60.f;
	gapY = 60.f;
	skin1Bool = false;
	skin2Bool = false;
	skin3Bool = false;
	victoryUnlocked = false;
	showPopup = false;

	shopClock.restart();

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

	shop2Text.setString("SHOP");
	shop2Text.setCharacterSize(300);
	shop2Text.setPosition({ static_cast<float>(STGS::GAP_X) + 5.f, static_cast<float>(STGS::HEIGHT * 0.01f) +5.f });
	shop2Text.setFillColor(sf::Color::Black);

	shopVictoryShape.setSize({ static_cast<float>(STGS::WIDTH / 3) - static_cast<float>(STGS::GAP_X), static_cast<float>(STGS::HEIGHT) * 1 / 3 - static_cast<float>(STGS::GAP_Y) });
	shopVictoryShape.setPosition({ static_cast<float>(STGS::WIDTH * 2 / 3 + STGS::GAP_X * 2 / 3), static_cast<float>(STGS::HEIGHT * 0.01f) });
	shopVictoryShape.setFillColor(sf::Color::Green);

	coin1.setSize({ 50, 50 });
	coin1.setPosition({ 20, 20 });
	coin1.setTexture(&Shared::goldTexture);

	coin2.setSize({ 50, 50 });
	coin2.setPosition({ shopCaseOneShape.getPosition().x + 10.f, shopCaseOneShape.getPosition().y + shopCaseOneShape.getGlobalBounds().size.y - coin2.getGlobalBounds().size.y - 10.f});
	coin2.setTexture(&Shared::goldTexture);

	coin3.setSize({ 50, 50 });
	coin3.setPosition({ shopCaseTwoShape.getPosition().x + 10.f, shopCaseTwoShape.getPosition().y + shopCaseTwoShape.getGlobalBounds().size.y - coin3.getGlobalBounds().size.y - 10.f });
	coin3.setTexture(&Shared::goldTexture);

	coin4.setSize({ 50, 50 });
	coin4.setPosition({ shopCaseThreeShape.getPosition().x + 10.f, shopCaseThreeShape.getPosition().y + shopCaseThreeShape.getGlobalBounds().size.y - coin4.getGlobalBounds().size.y - 10.f });
	coin4.setTexture(&Shared::goldTexture);

	coin5.setSize({ 50, 50 });
	coin5.setPosition({ shopVictoryShape.getPosition().x + 10.f, shopVictoryShape.getPosition().y + shopVictoryShape.getGlobalBounds().size.y - coin5.getGlobalBounds().size.y - 10.f });
	coin5.setTexture(&Shared::goldTexture);

	rect1.setSize({ shopCaseOneShape.getGlobalBounds().size.x, shopCaseOneShape.getGlobalBounds().size.y - gapY});
	rect1.setPosition({ shopCaseOneShape.getPosition().x, shopCaseOneShape.getPosition().y  });
	rect1.setTexture(&Shared::cadre1);

	rect2.setSize({ shopCaseTwoShape.getGlobalBounds().size.x, shopCaseTwoShape.getGlobalBounds().size.y - gapY });
	rect2.setPosition({ shopCaseTwoShape.getPosition().x , shopCaseTwoShape.getPosition().y });
	rect2.setTexture(&Shared::cadre1);

	rect3.setSize({ shopCaseThreeShape.getGlobalBounds().size.x, shopCaseThreeShape.getGlobalBounds().size.y - gapY });
	rect3.setPosition({ shopCaseThreeShape.getPosition().x, shopCaseThreeShape.getPosition().y });
	rect3.setTexture(&Shared::cadre1);

	rect4.setSize({ shopVictoryShape.getGlobalBounds().size.x, shopVictoryShape.getGlobalBounds().size.y - gapY });
	rect4.setPosition({ shopVictoryShape.getPosition().x, shopVictoryShape.getPosition().y});
	rect4.setTexture(&Shared::cadre1);

	skin1Text.setString("10 - Uranium guy");
	skin1Text.setCharacterSize(40);
	skin1Text.setPosition({ coin2.getPosition().x + coin2.getGlobalBounds().size.x, coin2.getPosition().y });

	skin2Text.setString("15 - Phosphorus guy");
	skin2Text.setCharacterSize(40);
	skin2Text.setPosition({ coin3.getPosition().x + coin3.getGlobalBounds().size.x, coin3.getPosition().y });

	skin3Text.setString("20 - Golden power");
	skin3Text.setCharacterSize(40);
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

	popupBox.setSize({ 1300, 200 });
	popupBox.setFillColor(sf::Color(0, 0, 0, 200));
	popupBox.setOutlineThickness(3);
	popupBox.setOutlineColor(sf::Color::White);
	popupBox.setOrigin(popupBox.getSize() / 2.f);
	popupBox.setPosition({ static_cast<float>(STGS::WIDTH / 2.f), static_cast<float>(STGS::HEIGHT / 2.f) });

	popupText.setFont(font);
	popupText.setCharacterSize(40);
	popupText.setFillColor(sf::Color::White);

	trophyShape.setSize({ rect4.getGlobalBounds().size.x - gapX * 2, rect4.getGlobalBounds().size.y - gapY });
	trophyShape.setPosition({ rect4.getPosition().x + gapX , rect4.getPosition().y + gapY / 2 });
	trophyShape.setTexture(&Shared::trophyTexture);
}

Shop::~Shop() {}

void Shop::reset() {
	skin1Bool = false;
	skin2Bool = false;
	skin3Bool = false;
	victoryUnlocked = false;
	showPopup = false;
}

void Shop::update(int& gold) {
	std::string tempString = std::to_string(gold);
	goldText.setString(tempString);

	sf::Vector2f mousePos = { static_cast<float>(sf::Mouse::getPosition().x), static_cast<float>(sf::Mouse::getPosition().y) };

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

	animRun.y = 0;

	if (clockRun.getElapsedTime().asMilliseconds() > 55) { 
		animRun.x++; 
		clockRun.restart();
	}
	if (animRun.x > 5)
		animRun.x = 0;
	skinOneShape.setTextureRect(sf::IntRect({ animRun.x * CHARACTER_ASSET_SIZE, animRun.y * CHARACTER_ASSET_SIZE }, { CHARACTER_ASSET_SIZE, CHARACTER_ASSET_SIZE })); 
	skinTwoShape.setTextureRect(sf::IntRect({ animRun.x * CHARACTER_ASSET_SIZE, animRun.y * CHARACTER_ASSET_SIZE }, { CHARACTER_ASSET_SIZE, CHARACTER_ASSET_SIZE }));
	skinThreeShape.setTextureRect(sf::IntRect({ animRun.x * CHARACTER_ASSET_SIZE, animRun.y * CHARACTER_ASSET_SIZE }, { CHARACTER_ASSET_SIZE, CHARACTER_ASSET_SIZE }));
}


void Shop::render(sf::RenderWindow& window) {
	window.draw(shopBackgroundShape);
	window.draw(shopCaseOneShape);
	window.draw(shopCaseTwoShape);
	window.draw(shopCaseThreeShape);
	window.draw(shop2Text);
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
	window.draw(trophyShape);
}

void Shop::buying(int& gold) {
	sf::Vector2f mousePos = { static_cast<float>(sf::Mouse::getPosition().x), static_cast<float>(sf::Mouse::getPosition().y) };

	const int priceSkin1 = 10;
	const int priceSkin2 = 15;
	const int priceSkin3 = 20;
	const int priceVictory = 50;

	auto tryBuySkin = [&](sf::RectangleShape& shape, int price, bool& skinBool, const std::string& skinName) {
		if (shape.getGlobalBounds().contains(mousePos) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && shopClock.getElapsedTime().asSeconds() > 1.f) {
			if (gold >= price) {
				gold -= price;
				skin1Bool = false;
				skin2Bool = false;
				skin3Bool = false;
				skinBool = true;

				showMessage("Vous achetez et equipez " + skinName + " !");

				shopClock.restart();
			}
			else {
				showMessage("Vous n'avez pas assez d'argent pour acheter le " + skinName + " !");

				shopClock.restart();
			}
		}
	};

	tryBuySkin(shopCaseOneShape, priceSkin1, skin1Bool, "Skin 1");
	tryBuySkin(shopCaseTwoShape, priceSkin2, skin2Bool, "Skin 2");
	tryBuySkin(shopCaseThreeShape, priceSkin3, skin3Bool, "Skin 3");

	if (shopVictoryShape.getGlobalBounds().contains(mousePos) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && shopClock.getElapsedTime().asSeconds() > 1.f) {
		if (gold >= priceVictory) {
			gold -= priceVictory;
			showMessage("Vous achetez la VICTOIRE !");
			victoryUnlocked = true;
			shopClock.restart();
		}
		else {
			showMessage("Vous n'avez pas assez d'argent pour acheter la victoire !");
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

bool Shop::getVictoryUnlocked() {
	return victoryUnlocked;
}