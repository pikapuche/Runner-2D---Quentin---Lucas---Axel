#include "Map.hpp"

Map::Map() {
	createSeed();
	rng.seed(seed);
	makeGround();
}

Map::~Map() {}

void Map::reset() {
	for (auto* o : obstacles) {
		delete o;
	}
	obstacles.clear();

	for (auto* p : plateforms) {
		delete p;
	}
	plateforms.clear();

	for (auto* c : collectibles) {
		delete c;
	}
	collectibles.clear();

	difficulty = 1;
	delay = 0.f;

	createSeed();
	rng.seed(seed);

	makeGround();
}

void Map::removeObstacle(Obstacle* obs) {
	auto& v = obstacles;
	v.erase(std::remove(v.begin(), v.end(), obs), v.end());
	delete obs;
}

void Map::removeCollectible(Collectible* col) {
	auto& v = collectibles;
	v.erase(std::remove(v.begin(), v.end(), col), v.end());
	delete col;
}

void Map::render(sf::RenderWindow& window) {
	bg.render(window);

	for (auto& obstacle : obstacles)
		obstacle->render(window);
	
	for (auto& plateform : plateforms)
		plateform->render(window);
	
	for (auto& collectible : collectibles)
		collectible->render(window);
	
	window.draw(ground);
	window.draw(ground2);
}

void Map::run(float deltatime, int& score, sf::Clock& generateClock) {
    for (auto it = obstacles.begin(); it != obstacles.end(); ) {
        auto& obstacle = *it;
        obstacle->move(deltatime, difficulty);
		obstacle->init();

        if (obstacle->shape.getPosition().x + obstacle->shape.getSize().x < 0) {
			delete obstacle;
            it = obstacles.erase(it);
			incrementScore(score);
        }
        else {
            ++it;
        }
    }

	for (auto it = plateforms.begin(); it != plateforms.end(); ) {
		auto& plateform = *it;
		plateform->move(deltatime, difficulty);

		if (plateform->shape.getPosition().x + plateform->shape.getSize().x < 0) {
			delete plateform;
			it = plateforms.erase(it);
			score++;
		}
		else {
			++it;
		}
	}

	for (auto it = collectibles.begin(); it != collectibles.end();) {
		auto& collectible = *it;
		collectible->move(deltatime);

		if (collectible->getShape().getPosition().x + collectible->getShape().getSize().x < 0) {
			delete collectible;
			it = collectibles.erase(it);
			score++;
		}
		else {
			++it;
		}
	}

	delay = 2.0f * std::exp(-0.03f * (score - 1)) + 0.8f;

	if (generateClock.getElapsedTime().asSeconds() > delay) {
		setObstacles(score);
		generateClock.restart();
	}
	if (score < 50)
		difficulty = 1;
	else if (score < 100) {
		if (difficulty == 1) {
			bg.startFlashTransition(2);
		}
		difficulty = 2;
	}
	else if (score < 200) {
		if (difficulty == 2) {
			bg.startFlashTransition(3);
		}
		difficulty = 3;
	}
	else if (score >= 200) {
		if (difficulty == 3) {
			bg.startFlashTransition(4);
		}
		difficulty = 4;
	}

	bg.setBackgroundTexture(difficulty);
	bg.move(deltatime, difficulty);
	moveGround(deltatime);
}

void Map::createSeed() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(100, 999);
	seed = dist(gen);
	std::cout << "seed : " << seed << std::endl;
}

void Map::makeGround() {
	ground.setSize(sf::Vector2f(STGS::WIDTH, STGS::HEIGHT / 10));
	ground.setPosition(sf::Vector2f(0, STGS::HEIGHT - ground.getSize().y));

	ground.setTextureRect(sf::IntRect({ 320, 0 }, { 96, 32 }));
	ground.setTexture(&Shared::groundTexture);

	ground2.setSize(sf::Vector2f(STGS::WIDTH, STGS::HEIGHT / 10));
	ground2.setPosition(sf::Vector2f(STGS::WIDTH * 0.9, STGS::HEIGHT - ground.getSize().y));

	ground2.setTextureRect(sf::IntRect({ 320, 0 }, { 96, 32 })); 
	ground2.setTexture(&Shared::groundTexture);
}

void Map::moveGround(float deltaTime) {
	const float groundSpeed = 400.f;

	ground.move({ -groundSpeed * deltaTime, 0.f });
	ground2.move({ -groundSpeed * deltaTime, 0.f });

	if (ground.getPosition().x + ground.getSize().x < 0)
		ground.setPosition({ ground2.getPosition().x + ground2.getSize().x, ground.getPosition().y });

	if (ground2.getPosition().x + ground2.getSize().x < 0)
		ground2.setPosition({ ground.getPosition().x + ground.getSize().x, ground2.getPosition().y });
}

void Map::setObstacles(int& score) {
	std::vector<int> lines = { 0, 1, 2 };
	std::shuffle(lines.begin(), lines.end(), rng);
	std::uniform_int_distribution<int> dist(0, 999);

	int waveType = dist(rng);

	int nbObstacles;
	if (waveType < 700 - difficulty * 10)
		nbObstacles = 1;
	else
		nbObstacles = 2;

	waveType += difficulty * 5;

	if (waveType < 333) {
		std::vector<int> platformLines = { 1, 2 };
		int linePlatform = platformLines[rand() % platformLines.size()];

		Plateform* tempPlatform = new Plateform(-500.f - score * 10.f, linePlatform);
		tempPlatform->shape.setSize({ static_cast<float>(STGS::WIDTH / 5), static_cast<float>((STGS::HEIGHT / 3 - STGS::GAP_Y - ground.getSize().y) / 2) });

		Collectible* tempCollectible = new Collectible(-500.f - score * 10.f, linePlatform);
		tempCollectible->getShape().setSize({ static_cast<float>(STGS::WIDTH * 0.04f), static_cast<float>(STGS::WIDTH * 0.04f) });

		float platformY;
		if (linePlatform == 1)
			platformY = static_cast<float>(STGS::HEIGHT / 3 + STGS::GAP_Y / 2 - ground.getSize().y / 2 + ground.getSize().y);
		else 
			platformY = static_cast<float>(STGS::HEIGHT * 2 / 3 + STGS::GAP_Y / 2 - ground.getSize().y + ground.getSize().y);

		tempPlatform->shape.setPosition({ static_cast<float>(STGS::WIDTH), platformY });

		tempCollectible->getShape().setPosition({
			STGS::WIDTH + tempPlatform->shape.getSize().x / 2 - tempCollectible->getShape().getSize().x / 2,
			platformY - tempCollectible->getShape().getSize().y - 10.f
			});

		plateforms.push_back(tempPlatform);
		collectibles.push_back(tempCollectible);
	}
	
	else if (waveType < 900){
		for (int i = 0; i < nbObstacles; ++i) {
			int line = lines[i];

			Obstacle* temp = new Obstacle(-500.f - score * 10.f, line);
			temp->shape.setSize({ static_cast<float>(STGS::WIDTH / 5), static_cast<float>(STGS::HEIGHT / 3 - STGS::GAP_Y)  });

			if (line == 0)
				temp->shape.setPosition({ static_cast<float>(STGS::WIDTH), static_cast<float>(0 + STGS::GAP_Y / 2) });
			else if (line == 1)
				temp->shape.setPosition({ static_cast<float>(STGS::WIDTH), static_cast<float>(STGS::HEIGHT / 3 + STGS::GAP_Y / 2)  });
			else {
				if (waveType % 2 == 0)
					temp->shape.setSize({ static_cast<float>(STGS::WIDTH / 5), static_cast<float>(STGS::HEIGHT / 3 - STGS::GAP_Y) / 2.5f });
				else 
					temp->shape.setSize({ static_cast<float>(STGS::WIDTH / 5), static_cast<float>(STGS::HEIGHT / 3 - STGS::GAP_Y) });
				temp->shape.setPosition({ static_cast<float>(STGS::WIDTH), static_cast<float>(STGS::HEIGHT * 2 / 3 + STGS::GAP_Y / 2) });
			}
			obstacles.push_back(temp);
		}
	}
	else {
		Obstacle* temp1 = new Obstacle(-500.f - score * 10.f, 0);
		temp1->shape.setSize({ static_cast<float>(STGS::WIDTH / 5), static_cast<float>(STGS::HEIGHT / 3 - STGS::GAP_Y) });
		temp1->shape.setPosition({ static_cast<float>(STGS::WIDTH), static_cast<float>(0 + STGS::GAP_Y / 2) });

		Obstacle* temp2 = new Obstacle(-500.f - score * 10.f, 1);
		temp2->shape.setSize({ static_cast<float>(STGS::WIDTH / 5), static_cast<float>(STGS::HEIGHT / 3 - STGS::GAP_Y) });
		temp2->shape.setPosition({ static_cast<float>(STGS::WIDTH), static_cast<float>(STGS::HEIGHT / 3 + STGS::GAP_Y / 2) });

		Obstacle* temp3 = new Obstacle(-500.f - score * 10.f, 1);
		temp3->shape.setSize({ static_cast<float>(STGS::WIDTH / 5), static_cast<float>(STGS::HEIGHT / 3 - STGS::GAP_Y) / 2.5f });
		temp3->shape.setPosition({ static_cast<float>(STGS::WIDTH), static_cast<float>(STGS::HEIGHT * 2 / 3 + STGS::GAP_Y / 2) });

		obstacles.push_back(temp1);
		obstacles.push_back(temp2);
		obstacles.push_back(temp3);
	}
}

std::vector<Obstacle*> Map::getVectObs() { return obstacles; }
std::vector<Collectible*> Map::getCollectible() { return collectibles; }
std::vector<Plateform*> Map::getPlateform() { return plateforms; }
sf::FloatRect Map::getBounds() { return ground.getGlobalBounds(); }
sf::FloatRect Map::getBounds2() { return ground2.getGlobalBounds(); }
int Map::getDifficulty() { return difficulty; }
sf::RectangleShape Map::getGround() { return ground; }
sf::RectangleShape Map::getGround2() { return ground2; }
std::vector<Plateform*> Map::getPlatformVector() { return plateforms; }
void Map::incrementScore(int& score) { score++; }