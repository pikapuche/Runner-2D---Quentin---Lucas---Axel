#include "Background.hpp"

Background::Background()  { // TODO : ADD BIOMES (depend to game difficulty). 4 biomes / 3 transition textures 
	// --- BIOME 1 : facile ---
	if (!backboardFirstTextureDifficultyOne.loadFromFile("Assets/tiles_map/backgroundFar.png"))
		std::cerr << "Erreur : backgroundFar.png introuvable" << std::endl;
	if (!backboardSecondTextureDifficultyOne.loadFromFile("Assets/tiles_map/backgroundNear.png"))
		std::cerr << "Erreur : backgroundNear.png introuvable" << std::endl;

	// --- BIOME 2 : normal ---
	if (!backboardFirstTextureDifficultyTwo.loadFromFile("Assets/tiles_map/backgroundFar_2.png"))
		std::cerr << "Erreur : backgroundFar_2.png introuvable" << std::endl;
	if (!backboardSecondTextureDifficultyTwo.loadFromFile("Assets/tiles_map/backgroundNear_2.png"))
		std::cerr << "Erreur : backgroundNear_2.png introuvable" << std::endl;

	// --- BIOME 3 : difficile ---
	if (!backboardFirstTextureDifficultyThree.loadFromFile("Assets/tiles_map/backgroundFar_3.png"))
		std::cerr << "Erreur : backgroundFar_3.png introuvable" << std::endl;
	if (!backboardSecondTextureDifficultyThree.loadFromFile("Assets/tiles_map/backgroundNear_3.png"))
		std::cerr << "Erreur : backgroundNear_3.png introuvable" << std::endl;

	// --- BIOME 4 : extrême ---
	if (!backboardFirstTextureDifficultyFour.loadFromFile("Assets/tiles_map/backgroundFar_4.png"))
		std::cerr << "Erreur : backgroundFar_4.png introuvable" << std::endl;
	if (!backboardSecondTextureDifficultyFour.loadFromFile("Assets/tiles_map/backgroundNear_4.png"))
		std::cerr << "Erreur : backgroundNear_4.png introuvable" << std::endl;

	backboardFirstShape.setTexture(&backboardFirstTextureDifficultyOne);
	backboardFirstShape.setPosition({ 0, 0 });
	backboardFirstShape.setSize({ static_cast<float>(STGS::WIDTH), static_cast<float>(STGS::HEIGHT) });

	backboardFirstShape2.setPosition({ static_cast<float>(STGS::WIDTH), 0 });
	backboardFirstShape2.setTexture(&backboardFirstTextureDifficultyOne);
	backboardFirstShape2.setSize({ static_cast<float>(STGS::WIDTH), static_cast<float>(STGS::HEIGHT) });

	backboardSecondShape.setTexture(&backboardSecondTextureDifficultyOne);
	backboardSecondShape.setPosition({ 0, 0 });
	backboardSecondShape.setSize({ static_cast<float>(STGS::WIDTH), static_cast<float>(STGS::HEIGHT) });

	flashOverlay.setSize({ static_cast<float>(STGS::WIDTH), static_cast<float>(STGS::HEIGHT) });
	flashOverlay.setFillColor(sf::Color(255, 255, 255, 0));
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

	if (isFlashing) {
		flashTimer += deltaTime;

		if (flashTimer < flashDuration / 2.f) {
			float alpha = (flashTimer / (flashDuration / 2.f)) * 255.f;
			flashOverlay.setFillColor(sf::Color(255, 255, 255, static_cast<std::uint8_t>(std::clamp(alpha, 0.f, 255.f))));
		}
		else if (flashTimer < flashDuration) {
			if (std::abs(flashTimer - flashDuration / 2.f) < deltaTime)
				setBackgroundTexture(currentDifficulty);

			float alpha = (1.f - ((flashTimer - flashDuration / 2.f) / (flashDuration / 2.f))) * 255.f;
			flashOverlay.setFillColor(sf::Color(255, 255, 255, static_cast<std::uint8_t>(std::clamp(alpha, 0.f, 255.f))));
		}
		else {
			isFlashing = false;
			flashOverlay.setFillColor(sf::Color(255, 255, 255, 0));
		}
	}
}

void Background::render(sf::RenderWindow& window) {
	window.draw(backboardFirstShape);
	window.draw(backboardFirstShape2);
	window.draw(backboardSecondShape);

	if (isFlashing)
		window.draw(flashOverlay);
}

void Background::setBackgroundTexture(int difficulty) {
	currentDifficulty = difficulty;
	switch (difficulty) {
	case 1:
		backboardFirstShape.setTexture(&backboardFirstTextureDifficultyOne);
		backboardFirstShape2.setTexture(&backboardFirstTextureDifficultyOne);
		backboardSecondShape.setTexture(&backboardSecondTextureDifficultyOne);
		break;

	case 2:
		backboardFirstShape.setTexture(&backboardFirstTextureDifficultyTwo);
		backboardFirstShape2.setTexture(&backboardFirstTextureDifficultyTwo);
		backboardSecondShape.setTexture(&backboardSecondTextureDifficultyTwo);
		break;

	case 3:
		backboardFirstShape.setTexture(&backboardFirstTextureDifficultyThree);
		backboardFirstShape2.setTexture(&backboardFirstTextureDifficultyThree);
		backboardSecondShape.setTexture(&backboardSecondTextureDifficultyThree);
		break;

	case 4:
		backboardFirstShape.setTexture(&backboardFirstTextureDifficultyFour);
		backboardFirstShape2.setTexture(&backboardFirstTextureDifficultyFour);
		backboardSecondShape.setTexture(&backboardSecondTextureDifficultyFour);
		break;

	default:
		backboardFirstShape.setTexture(&backboardFirstTextureDifficultyOne);
		backboardFirstShape2.setTexture(&backboardFirstTextureDifficultyOne);
		backboardSecondShape.setTexture(&backboardSecondTextureDifficultyOne);
		break;
	}
}

void Background::startFlashTransition(int newDifficulty) {
	if (newDifficulty == currentDifficulty) return;

	isFlashing = true;
	flashTimer = 0.f;

	currentDifficulty = newDifficulty;
}