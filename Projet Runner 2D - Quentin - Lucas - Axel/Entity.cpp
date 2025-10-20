#include "Entity.hpp"

Entity::Entity(float posX, float posY) : sprite(texture)
{
	position.x = posX;
	position.y = posY;
}

void Entity::collision(Sprite& tile, float deltaTime)
{

}

Sprite& Entity::getSprite()
{
	return sprite;
}
