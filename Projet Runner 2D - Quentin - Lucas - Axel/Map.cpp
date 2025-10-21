#include "Map.hpp"

Map::Map() {
	createSeed();
	rng.seed(seed);
	score = 0;
}

Map::~Map() {

}

void Map::init() {
	obstacles.clear();
	generate();
	for (auto& obstacle : obstacles) {
		obstacle->init();
	}

	std::cout << "taille vec : " << obstacles.size() << std::endl;
	std::cout << "seed : " << seed << std::endl;
}


void Map::render(sf::RenderWindow& window) {
	for (auto& obstacle : obstacles) {
		obstacle->render(window);
	}
}

void Map::run() {
    static bool hasSpawnedNextWave = false;

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
	std::cout << "score : " << score << std::endl;

    if (obstacles.empty())
    {
        init();
    }
}


void Map::generate() {
	std::uniform_real_distribution<float> speedDist(-6.f, -5.f);
	std::vector<int> lines = { 0, 1, 2 };
	std::shuffle(lines.begin(), lines.end(), rng);

	for (int i = 0; i < 2; ++i) {
		float speed = speedDist(rng);
		int line = lines[i];
		obstacles.push_back(new Obstacle(std::min(-1, -score), line));
	}
}

void Map::createSeed()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(100000, 999999);
	seed = dist(gen);
}