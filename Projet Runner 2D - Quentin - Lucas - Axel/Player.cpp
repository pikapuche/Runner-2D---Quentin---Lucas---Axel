#include "Player.hpp"

Player::Player(float xPos, float yPos) : Entity(xPos, yPos)
{
	position.y = 0;
	sprite.setPosition(position);
	//sprite.setColor(Color::Red);
	if (!texture.loadFromFile("Assets/Character/rect.jpg")) cout << "prout";
	sprite.setTexture(texture);
	cout << "Joueur créé" << endl;
}

Player::~Player()
{
	cout << "Joueur détruit" << endl;
}

void Player::playerMovement(float deltaTime)
{
	position.x += SPEED * deltaTime;

	velocity.y = gravity * deltaTime;
	position.y = velocity.y * deltaTime;
	sprite.move(position);
}

void Player::update(float deltaTime)
{
	//playerMovement(deltaTime);
}

void Player::draw(RenderWindow& window)
{
	window.draw(sprite);
}
