#pragma once

#include "Entity.hpp"
#include "Map.hpp"

class Player : public Entity {
protected : 

	const float JUMP_FORCE = 40.f; // force initiale du saut
	const float JETPACK_FORCE = 5.f;
	const int CHARACTER_ASSET_SIZE = 128;

	float jetpackStamina = 100.f;
	RectangleShape staminaBar;
	RectangleShape staminaBarRect;

	float jumpCount; // compteur de saut

	Clock clockRun; // Clock qui permet de modifier la vitesse d'anim
	Clock clockJump; // Clock qui permet de modifier la vitesse d'anim
	Clock clockSecondJump; // Clock qui permet de modifier le temps entre le premier et le deuxieme saut
	Clock clockJetpack; // Clock quand on est pour l'anim jetpack


	Texture textureJump; // Texture du saut
	Texture textureJetpack; // Texture du saut

	Vector2i animRun;
	Vector2i animJump;
	Vector2i animJetpack;

	bool isJumping = false; // le joueur saute ?

	float volumeSound; // valeur du volume pour les sons

	//SoundBuffer bufferJump; // comment marchent les sons ????
	//SoundBuffer bufferDoubleJump;


public :

	enum State { GROUNDED, JUMP }; // enum qui permet de savoir si le joueur est au sol ou non
	State state;

	enum MoveState { RUNNING, JUMPING, JETPACKING }; // enum qui permet de savoir si le joueur cours, saute ou dash (sert aux anim)
	MoveState stateMove;

	Player(float xPos, float yPos);
	~Player();

	void playerMovement(float deltaTime, Map& map); // controle les mouvements du player

	bool collision(Map& map);

	//void dash(float deltaTime);

	void jump(float deltaTime); // fonction de saut

	void animationManager(float deltaTime); // gère les animations du personnage avec un switch et un enum

	void jetpackStaminaGestion();

	//Vector2f getVelocity();

	//Vector2f setVelocity(float veloX, float veloY);

	//void soundManager();

	//void setColliderMap(float left, float right);

	//void animationManager(float deltaTime);

	void update(float deltaTime, Map& map); // update les fonctions du player avec le deltaTime

	void draw(RenderWindow& window) override; // draw le player
};