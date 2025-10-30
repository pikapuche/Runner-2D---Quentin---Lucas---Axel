#include "Background.hpp"

Background::Background() {
	speedFar = 100.f;
	speedNear = 200.f;

	flashDuration = 0.3f;
	isFlashing = false;
	flashTimer = 0.f;

	currentDifficulty = 1;

	backboardFirstShape.setTexture(&Shared::backboardFirstTextureDifficultyOne);
	backboardFirstShape.setPosition({ 0, 0 });
	backboardFirstShape.setSize({ static_cast<float>(STGS::WIDTH), static_cast<float>(STGS::HEIGHT) });

	backboardFirstShape2.setPosition({ static_cast<float>(STGS::WIDTH), 0 });
	backboardFirstShape2.setTexture(&Shared::backboardFirstTextureDifficultyOne);
	backboardFirstShape2.setSize({ static_cast<float>(STGS::WIDTH), static_cast<float>(STGS::HEIGHT) });

	backboardSecondShape.setTexture(&Shared::backboardSecondTextureDifficultyOne);
	backboardSecondShape.setPosition({ 0, 0 });
	backboardSecondShape.setSize({ static_cast<float>(STGS::WIDTH), static_cast<float>(STGS::HEIGHT) });

	flashOverlay.setSize({ static_cast<float>(STGS::WIDTH), static_cast<float>(STGS::HEIGHT) });
	flashOverlay.setFillColor(sf::Color(255, 255, 255, 0));
}

Background::~Background() {}

void Background::move(float deltaTime, int difficulty) {
	setCurrentDifficulty(difficulty);

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
		backboardFirstShape.setTexture(&Shared::backboardFirstTextureDifficultyOne, true);
		backboardFirstShape2.setTexture(&Shared::backboardFirstTextureDifficultyOne, true);
		backboardSecondShape.setTexture(&Shared::backboardSecondTextureDifficultyOne, true);
		break;

	case 2:
		backboardFirstShape.setTexture(&Shared::backboardFirstTextureDifficultyTwo);
		backboardFirstShape2.setTexture(&Shared::backboardFirstTextureDifficultyTwo);
		backboardSecondShape.setTexture(&Shared::backboardSecondTextureDifficultyTwo);
		break;

	case 3:
		backboardFirstShape.setTexture(&Shared::backboardFirstTextureDifficultyThree);
		backboardFirstShape2.setTexture(&Shared::backboardFirstTextureDifficultyThree);
		backboardSecondShape.setTexture(&Shared::backboardSecondTextureDifficultyThree);
		break;

	case 4:
		backboardFirstShape.setTexture(&Shared::backboardFirstTextureDifficultyFour);
		backboardFirstShape2.setTexture(&Shared::backboardFirstTextureDifficultyFour);
		backboardSecondShape.setTexture(&Shared::backboardSecondTextureDifficultyFour);
		break;

	default:
		backboardFirstShape.setTexture(&Shared::backboardFirstTextureDifficultyOne);
		backboardFirstShape2.setTexture(&Shared::backboardFirstTextureDifficultyOne);
		backboardSecondShape.setTexture(&Shared::backboardSecondTextureDifficultyOne);
		break;
	}
}

void Background::startFlashTransition(int newDifficulty) {
	if (newDifficulty == currentDifficulty) return;

	isFlashing = true;
	flashTimer = 0.f;

	currentDifficulty = newDifficulty;
}

void Background::setCurrentDifficulty(int difficulty) {
	currentDifficulty = difficulty;
}