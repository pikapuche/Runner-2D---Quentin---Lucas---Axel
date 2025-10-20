#include "Map.hpp"

Map::Map() {

}

Map::~Map() {

}

void Map::init() {
	generate();

	for (auto& obstacle : obstacles) {
		obstacle->init();
		if (obstacle->getLine() == 0)
			obstacle->setPosition({ STGS::WIDTH / 2.f, 0 + STGS::GAP_Y / 2 });
		else if (obstacle->getLine() == 1)
			obstacle->setPosition({ STGS::WIDTH / 2.f, STGS::HEIGHT * 1 / 3 + STGS::GAP_Y / 2 });
		else if (obstacle->getLine() == 2)
			obstacle->setPosition({ STGS::WIDTH / 2.f, STGS::HEIGHT * 2 / 3 + STGS::GAP_Y / 2 });
		std::cout << "line : " << obstacle->getLine() << std::endl;
		std::cout << "pos : " << obstacle->shape.getPosition().y << std::endl;
	}
	std::cout << "taille vec : " << obstacles.size() << std::endl;
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

		if (obstacle->shape.getPosition().x < 0)
		{
			it = obstacles.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void Map::generate() {
	srand(static_cast<unsigned int>(time(nullptr)));
	for (int i = 0; i < 3; i++)
	{
		obstacles.push_back(new Obstacle( - 0.2f, i));
	}
}