#include "Map.hpp"

Map::Map() {
	createSeed();
	rng.seed(seed);
	std::cout << "seed : " << seed << std::endl;
	score = 50;
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


	if (obstacles[obstacles.size()-1]->shape.getPosition().x < STGS::WIDTH / 2 || obstacles.empty())
	{
		generate();
	}
}


void Map::setObstacles() {
	std::vector<int> lines = { 0, 1, 2 };
	std::shuffle(lines.begin(), lines.end(), rng);

	for (int i = 0; i < 2; ++i) {
		int line = lines[i];
		Obstacle* temp = new Obstacle(-500.0f - score * 10.0f, line);

		temp->shape.setFillColor(sf::Color::Red);
		temp->shape.setSize({ STGS::WIDTH / 5, STGS::HEIGHT / 3 - STGS::GAP_Y });

		if (temp->getLine() == 0)
			temp->shape.setPosition({ STGS::WIDTH, 0 + STGS::GAP_Y / 2 });
		else if (temp->getLine() == 1)
			temp->shape.setPosition({ STGS::WIDTH, STGS::HEIGHT * 1 / 3 + STGS::GAP_Y / 2 });
		else if (temp->getLine() == 2)
			temp->shape.setPosition({ STGS::WIDTH, STGS::HEIGHT * 2 / 3 + STGS::GAP_Y / 2 });

		obstacles.push_back(temp);
	}
}

void Map::createSeed()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(100000, 999999);
	seed = dist(gen);
}