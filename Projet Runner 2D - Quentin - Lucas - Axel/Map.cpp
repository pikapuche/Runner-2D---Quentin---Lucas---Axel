#include "Map.hpp"

Map::Map() {
	createSeed();
	rng.seed(seed);
	std::cout << "seed : " << seed << std::endl;

	makeGround();

	if (!groundTexture.loadFromFile("Assets/tiles_map/RunnerTileSet.png")) {
		std::cerr << "Erreur chargement texture" << std::endl;
	}
	generateClock.start();
}

Map::~Map() {

}

void Map::generate() {
	//obstacles.clear();
	setObstacles();

	//std::cout << "taille vec : " << obstacles.size() << std::endl;
}


void Map::render(sf::RenderWindow& window) {
	bg.render(window);
	for (auto& obstacle : obstacles) {
		obstacle->render(window);
	}
	for (auto& plateform : plateforms) {
		plateform->render(window);
	}
	for (auto& collectible : collectibles) {
		collectible->render(window);
	}
	window.draw(ground);
	window.draw(ground2);
}

void Map::run(float deltatime) {

    for (auto it = obstacles.begin(); it != obstacles.end(); )
    {
        auto& obstacle = *it;
        obstacle->move(deltatime);
		obstacle->init();

        if (obstacle->shape.getPosition().x + obstacle->shape.getSize().x < 0)
        {
            it = obstacles.erase(it);
			_score++;
        }
        else
        {
            ++it;
        }
    }
	//std::cout << "score : " << score << std::endl;

	for (auto it = plateforms.begin(); it != plateforms.end(); ) {
		auto& plateform = *it;
		plateform->move(deltatime);

		if (plateform->shape.getPosition().x + plateform->shape.getSize().x < 0) {
			it = plateforms.erase(it);
			_score++;
		}
		else {
			++it;
		}
	}

	for (auto it = collectibles.begin(); it != collectibles.end(); ) {
		auto& collectible = *it;
		collectible->move(deltatime);

		if (collectible->shape.getPosition().x + collectible->shape.getSize().x < 0) {
			it = collectibles.erase(it);
			_score++;
		}
		else {
			++it;
		}
	}

	//std::cout << "score : " << score << std::endl;
	delay = 2.0f * std::exp(-0.03f * (_score - 1)) + 0.8f;
	if (generateClock.getElapsedTime().asSeconds() > delay) {
		generate();
		generateClock.restart();
	}
	if (_score < 50)
		difficulty = 1;
	else if (_score < 100)
		difficulty = 2;
	else if (_score < 200)
		difficulty = 3;
	else
		difficulty = 4;

	bg.move(deltatime);
	moveGround(deltatime);
}

void Map::setObstacles() {
	std::vector<int> lines = { 0, 1, 2 };
	std::shuffle(lines.begin(), lines.end(), rng);

	int waveType = rand() % 100;

	int nbObstacles;
	if (waveType < 70 - difficulty * 10)
		// difficulty 1 = 60% de chance d'avoir un seul obstacle //// 50% pour la difficulty 2 //// 40% de chance pour la difficult� 3 //// 30% de chance pour la difficult� 4
		nbObstacles = 1;
	else
		nbObstacles = 2;

	waveType += difficulty * 5; // plus de chance d'avoir des plateforms en debut de partie

	if (waveType < 33) {
		std::vector<int> platformLines = { 1, 2 };
		int linePlatform = platformLines[rand() % platformLines.size()];

		Plateform* tempPlatform = new Plateform(-500.f - _score * 10.f, linePlatform);
		tempPlatform->shape.setSize({ static_cast<float>(STGS::WIDTH / 5), static_cast<float>((STGS::HEIGHT / 3 - STGS::GAP_Y - ground.getSize().y) / 2) });

		Collectible* tempCollectible = new Collectible(-500.f - _score * 10.f, linePlatform);
		tempCollectible->shape.setSize({ static_cast<float>(STGS::WIDTH * 0.04f), static_cast<float>((STGS::HEIGHT / 3 - STGS::GAP_Y - ground.getSize().y) / 2) });

		float platformY;
		if (linePlatform == 1) {
			platformY = static_cast<float>(STGS::HEIGHT / 3 + STGS::GAP_Y / 2 - ground.getSize().y / 2 + ground.getSize().y);
		}
		else {
			platformY = static_cast<float>(STGS::HEIGHT * 2 / 3 + STGS::GAP_Y / 2 - ground.getSize().y + ground.getSize().y);
		}

		tempPlatform->shape.setPosition({ static_cast<float>(STGS::WIDTH), platformY });

		tempCollectible->shape.setPosition({
			STGS::WIDTH + tempPlatform->shape.getSize().x / 2 - tempCollectible->shape.getSize().x / 2,
			platformY - tempCollectible->shape.getSize().y - 10.f
			});

		plateforms.push_back(tempPlatform);
		collectibles.push_back(tempCollectible);
	}
	else {
		for (int i = 0; i < nbObstacles; ++i) {
			int line = lines[i];

			Obstacle* temp = new Obstacle(-500.f - _score * 10.f, line);
			temp->shape.setSize({ static_cast<float>(STGS::WIDTH / 5), static_cast<float>(STGS::HEIGHT / 3 - STGS::GAP_Y)  });

			if (line == 0)
				temp->shape.setPosition({ static_cast<float>(STGS::WIDTH), static_cast<float>(0 + STGS::GAP_Y / 2) });
			else if (line == 1)
				temp->shape.setPosition({ static_cast<float>(STGS::WIDTH), static_cast<float>(STGS::HEIGHT / 3 + STGS::GAP_Y / 2)  });
			else
				temp->shape.setPosition({ static_cast<float>(STGS::WIDTH), static_cast<float>(STGS::HEIGHT * 2 / 3 + STGS::GAP_Y / 2)  });

			obstacles.push_back(temp);
		}
	}
}

void Map::createSeed()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(100000, 999999);
	seed = dist(gen);
}

void Map::makeGround() {
	ground.setSize(sf::Vector2f(STGS::WIDTH, STGS::HEIGHT / 10));
	ground.setPosition(sf::Vector2f(0, STGS::HEIGHT - ground.getSize().y));

	ground.setTextureRect(sf::IntRect({ 320, 0 }, { 96, 32 })); // 1 tile = 32px //// 3 tiles = 96px
	ground.setTexture(&groundTexture);

	ground2.setSize(sf::Vector2f(STGS::WIDTH, STGS::HEIGHT / 10));
	ground2.setPosition(sf::Vector2f(STGS::WIDTH * 0.9, STGS::HEIGHT - ground.getSize().y));

	ground2.setTextureRect(sf::IntRect({ 320, 0 }, { 96, 32 })); // 1 tile = 32px //// 3 tiles = 96px
	ground2.setTexture(&groundTexture);
}

std::vector<Obstacle*> Map::getVectObs()
{
	return obstacles;
}

void Map::moveGround(float deltaTime)
{
	const float groundSpeed = 400.f;

	ground.move({ -groundSpeed * deltaTime, 0.f });
	ground2.move({ -groundSpeed * deltaTime, 0.f });

	if (ground.getPosition().x + ground.getSize().x < 0)
		ground.setPosition({ ground2.getPosition().x + ground2.getSize().x, ground.getPosition().y });

	if (ground2.getPosition().x + ground2.getSize().x < 0)
		ground2.setPosition({ ground.getPosition().x + ground.getSize().x, ground2.getPosition().y });
}

sf::FloatRect Map::getBounds() {
	return ground.getGlobalBounds();
}

sf::FloatRect Map::getBounds2() {
	return ground2.getGlobalBounds();
}


int Map::getScore() {
	return _score;
}

int Map::getDifficulty() {
	return difficulty;
}

sf::RectangleShape Map::getGround() {
	return ground;
}

sf::RectangleShape Map::getGround2() {
	return ground2;
}

void Map::setScore(int score) {
	_score = score;
}