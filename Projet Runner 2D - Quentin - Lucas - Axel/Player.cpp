#include "Player.hpp"

Player::Player(float xPos, float yPos) : Entity(xPos, yPos)
{
	shape.setPosition(position);
	//sprite.setColor(Color::Blue);
	if (!texture.loadFromFile("Assets/Character/_Crouch.png")) cout << "prout" << endl << endl << endl << endl;
	shape.setTexture(&texture);
	shape.setSize(Vector2f(120, 80));
	shape.setScale(Vector2f(3, 3));
	cout << "Joueur créé" << endl;
}

Player::~Player()
{
	cout << "Joueur détruit" << endl;
}

void Player::playerMovement(float deltaTime)
{
	position.x = SPEED * deltaTime;

	velocity.y = gravity * deltaTime;
	position.y = velocity.y * deltaTime;
	shape.move(position);
}

void Player::update(float deltaTime)
{
	playerMovement(deltaTime);
}

void Player::draw(RenderWindow& window)
{
	window.draw(shape);
}
