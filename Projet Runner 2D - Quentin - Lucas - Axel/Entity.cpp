#include "Entity.hpp"

Entity::Entity(float posX, float posY)
{
	texture.setSmooth(true);
	position.x = posX;
	position.y = posY;
}

void Entity::collision(Sprite& tile, float deltaTime)
{

}
