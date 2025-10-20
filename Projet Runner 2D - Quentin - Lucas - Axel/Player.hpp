#pragma once

#include "Entity.hpp"

class Player : public Entity {
protected : 

	const float SPEED = 50.f;
	const float JUMP_FORCE = 100.f;

public :

	Player(float xPos, float yPos);
	~Player();

	void playerMovement(float deltaTime);

	//void dash(float deltaTime);

	//void jump();

	//Vector2f getVelocity();

	//Vector2f setVelocity(float veloX, float veloY);

	//void soundManager();

	//void setColliderMap(float left, float right);

	//void animationManager(float deltaTime);

	void update(float deltaTime);

	void draw(RenderWindow& window) override;

};