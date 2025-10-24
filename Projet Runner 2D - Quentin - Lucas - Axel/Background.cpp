#include "Background.hpp"

Background::Background()  { // TODO : ADD BIOMES (depend to game difficulty). 4 biomes / 3 transition textures 
	if (!backboardFirstTexture.loadFromFile("Assets/tiles_map/backgroundFar.png"))
		std::cerr << "backboardFirstTexture not found" << std::endl;
	if (!backboardSecondTexture.loadFromFile("Assets/tiles_map/backgroundNear.png"))
		std::cerr << "backboardSecondTexture not found" << std::endl;

	backboardFirstShape.setTexture(&backboardFirstTexture);
	backboardFirstShape.setPosition({ 0, 0 });
	backboardFirstShape.setSize({ static_cast<float>(STGS::WIDTH), static_cast<float>(STGS::HEIGHT) });

	backboardFirstShape2.setPosition({ static_cast<float>(STGS::WIDTH), 0 });
	backboardFirstShape2.setTexture(&backboardFirstTexture);
	backboardFirstShape2.setSize({ static_cast<float>(STGS::WIDTH), static_cast<float>(STGS::HEIGHT) });

	backboardSecondShape.setTexture(&backboardSecondTexture);
	backboardSecondShape.setPosition({ 0, 0 });
	backboardSecondShape.setSize({ static_cast<float>(STGS::WIDTH), static_cast<float>(STGS::HEIGHT) });
}

Background::~Background() {
}

void Background::init() {

}

void Background::move(float deltaTime) {
	const float speedFar = 100.f;
	const float speedNear = 200.f;

	backboardFirstShape.move({ -speedFar * deltaTime, 0.f });
	backboardFirstShape2.move({ -speedFar * deltaTime, 0.f });
	backboardSecondShape.move({ -speedNear * deltaTime, 0.f });

	if (backboardFirstShape.getPosition().x + STGS::WIDTH < 0)
		backboardFirstShape.setPosition({ backboardFirstShape2.getPosition().x + STGS::WIDTH, 0.f });

	if (backboardFirstShape2.getPosition().x + STGS::WIDTH < 0)
		backboardFirstShape2.setPosition({ backboardFirstShape.getPosition().x + STGS::WIDTH, 0.f });

	if (backboardSecondShape.getPosition().x + STGS::WIDTH < 0)
		backboardSecondShape.setPosition({ static_cast<float>(STGS::WIDTH), 0.f });
}

void Background::render(sf::RenderWindow& window) {
	window.draw(backboardFirstShape);
	window.draw(backboardFirstShape2);
	window.draw(backboardSecondShape);
}
