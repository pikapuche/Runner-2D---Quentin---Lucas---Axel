#include "Map.hpp"

Map::Map() {
	createSeed();
	rng.seed(seed);
	std::cout << "seed : " << seed << std::endl;
	score = 50;
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
	for (auto& obstacle : obstacles) {
		obstacle->render(window);
	}
	for (auto& plateform : plateforms) {
		plateform->render(window);
	}
	window.draw(ground);
}

void Map::run(float deltatime) {

    for (auto it = obstacles.begin(); it != obstacles.end(); )
    {
        auto& obstacle = *it;
        obstacle->move(deltatime);

        if (obstacle->shape.getPosition().x + obstacle->shape.getSize().x < 0)
        {
            it = obstacles.erase(it);
			score++;
        }
        else
        {
            ++it;
        }
    }
	//std::cout << "score : " << score << std::endl;

	for (auto it = plateforms.begin(); it != plateforms.end(); )
	{
		auto& plateform = *it;
		plateform->move(deltatime);

		if (plateform->shape.getPosition().x + plateform->shape.getSize().x < 0)
		{
			it = plateforms.erase(it);
			score++;
		}
		else
		{
			++it;
		}
	}
	//std::cout << "score : " << score << std::endl;
	if (generateClock.getElapsedTime().asSeconds() > 0.8f) {
		generate();
		generateClock.restart();
	}
}

void Map::setObstacles() {
	std::vector<int> lines = { 0, 1, 2 };
	std::shuffle(lines.begin(), lines.end(), rng);

	int waveType = rand() % 100;

	if (waveType < 20) 
	{
		std::vector<int> platformLines = { 1, 2 };
		int linePlatform = platformLines[rand() % platformLines.size()];

		Plateform* tempPlatform = new Plateform(-500.f - score * 10.f, linePlatform);
		tempPlatform->shape.setSize({ STGS::WIDTH / 5, STGS::HEIGHT / 3 - STGS::GAP_Y - ground.getSize().y });

		if (linePlatform == 1)
			tempPlatform->shape.setPosition({ STGS::WIDTH, STGS::HEIGHT / 3 + STGS::GAP_Y / 2 - ground.getSize().y / 2 });
		else
			tempPlatform->shape.setPosition({ STGS::WIDTH, STGS::HEIGHT * 2 / 3 + STGS::GAP_Y / 2 - ground.getSize().y });

		plateforms.push_back(tempPlatform);
	}
	else 
	{
		for (int i = 0; i < 2; ++i) {
			int line = lines[i];

			Obstacle* temp = new Obstacle(-500.f - score * 10.f, line);
			temp->shape.setSize({ STGS::WIDTH / 5, STGS::HEIGHT / 3 - STGS::GAP_Y - ground.getSize().y });

			if (line == 0)
				temp->shape.setPosition({ STGS::WIDTH, 0 + STGS::GAP_Y / 2 });
			else if (line == 1)
				temp->shape.setPosition({ STGS::WIDTH, STGS::HEIGHT / 3 + STGS::GAP_Y / 2 - ground.getSize().y / 2 });
			else
				temp->shape.setPosition({ STGS::WIDTH, STGS::HEIGHT * 2 / 3 + STGS::GAP_Y / 2 - ground.getSize().y });

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
}

sf::FloatRect Map::getBounds() {
	return ground.getGlobalBounds();
}