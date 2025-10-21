#include "Map.hpp"

Map::Map() {
	createSeed();
	rng.seed(seed);
	score = 20;
}

Map::~Map() {

}

void Map::init() {
	obstacles.clear();
	generate();

	std::cout << "taille vec : " << obstacles.size() << std::endl;
	std::cout << "seed : " << seed << std::endl;
}


void Map::render(sf::RenderWindow& window) {
	for (auto& obstacle : obstacles) {
		obstacle->render(window);
	}
}

void Map::run() {

    for (auto it = obstacles.begin(); it != obstacles.end(); )
    {
        auto& obstacle = *it;
        obstacle->move();

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


	if (obstacles[0]->shape.getPosition().x < STGS::WIDTH / 2 || obstacles.empty())
	{
		generate();
	}
}


void Map::generate() {
	std::uniform_real_distribution<float> speedDist(-6.f, -5.f);
	std::vector<int> lines = { 0, 1, 2 };
	std::shuffle(lines.begin(), lines.end(), rng);

	for (int i = 0; i < 2; ++i) {
		float speed = speedDist(rng);
		int line = lines[i];
		Obstacle* temp = new Obstacle(std::min(-1, -score), line);

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