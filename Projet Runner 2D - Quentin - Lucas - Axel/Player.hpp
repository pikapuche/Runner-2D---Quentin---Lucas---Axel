#pragma once

#include "Entity.hpp"

class Player : public Entity {
protected : 

	const float SPEED = 100.f; // vitesse du personnage
	const float JUMP_FORCE = 100.f; // force initiale du saut

	float jumpCount; // compteur de saut

	Clock runClock; // Clock qui permet de modifier la vitesse d'anim
	Clock jumpClock; // Clock qui permet de modifier la vitesse d'anim
	Clock secondJumpClock; // Clock qui permet de modifier le temps entre le premier et le deuxieme saut

	Texture textureJump; // Texture du saut

	bool isJumping = false; // le joueur saute ?

	float VolumeSound; // valeur du volume pour les sons

	//SoundBuffer bufferJump; // comment marchent les sons ????
	//SoundBuffer bufferDoubleJump;

public :

	enum State { GROUNDED, JUMP }; // enum qui permet de savoir si le joueur est au sol ou non
	State state;

	enum MoveState { RUNNING, JUMPING, DASHING }; // enum qui permet de savoir si le joueur cours, saute ou dash (sert aux anim)
	MoveState stateMove;

	Player(float xPos, float yPos);
	~Player();

	void playerMovement(float deltaTime); // controle les mouvements du player

	//void dash(float deltaTime);

	void jump(); // fonction de saut

	void animationManager(float deltaTime); // gère les animations du personnage avec un switch et un enum

	//Vector2f getVelocity();

	//Vector2f setVelocity(float veloX, float veloY);

	//void soundManager();

	//void setColliderMap(float left, float right);

	//void animationManager(float deltaTime);

	void update(float deltaTime); // update les fonctions du player avec le deltaTime

	void draw(RenderWindow& window) override; // draw le player
};