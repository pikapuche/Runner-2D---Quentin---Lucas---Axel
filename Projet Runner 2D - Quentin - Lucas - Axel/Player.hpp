#pragma once
#include "Entity.hpp"
#include "Map.hpp"

class Player : public Entity {
protected : 

	const float JUMP_FORCE = 40.f; // force initiale du saut
	const float JETPACK_FORCE = 15.f; // force de propulsion du jetpack
	const int CHARACTER_ASSET_SIZE = 128; // taille du character

	float jetpackStamina = 100.f; // endurance du jetpack
	RectangleShape staminaBar; // barre d'endurance du jetpack
	RectangleShape staminaBarRect; // outline de la barre d'endurance du jetpack maximale

	Clock clockRun; // Clock qui permet de modifier la vitesse d'anim
	Clock clockJump; // Clock qui permet de modifier la vitesse d'anim
	Clock clockSecondJump; // Clock qui permet de modifier le temps entre le premier et le deuxieme saut
	Clock clockJetpack; // Clock quand on est pour l'anim jetpack

	Texture textureJump; // Texture du saut
	Texture textureJetpack; // Texture du saut

	// Vector d'animation qui compte les frames
	Vector2i animRun; 
	Vector2i animJump;
	Vector2i animJetpack;

	int volumeSound = 100;
	
	SoundBuffer bufferRunGravel; // son quand le perso va courir
	SoundBuffer bufferRun; // son quand le perso va courir
	SoundBuffer bufferJump; // son quand le perso va sauter
	SoundBuffer bufferJetpack; // son quand le perso va utiliser le jetpack

	Sound sound;

	int life = 3;

	bool isInvincible = false;

public :

	enum State { NOTHING, GROUNDED, JUMP }; // enum qui permet de savoir si le joueur est au sol ou non
	State state;

	enum MoveState { NONE, RUNNING, JUMPING, JETPACKING }; // enum qui permet de savoir si le joueur cours, saute ou dash (sert aux anim)
	MoveState stateMove;

	Player();
	~Player();

	void playerMovement(float deltaTime, Map& map); // controle les mouvements du player

	void jump(float deltaTime); // fonction de saut

	bool collision(Map& map);

	void animationManager(float deltaTime); // gère les animations du personnage avec un switch et un enum

	void jetpackStaminaGestion();

	void death();

	FloatRect getFeetBounds() const;

	int getLife();

	void setLife(int l);

	void setLessLife();

	void setUpLife();

	void soundManager(SoundBuffer& buffer);

	void update(float deltaTime, Map& map); // update les fonctions du player avec le deltaTime

	void draw(RenderWindow& window) override; // draw le player
};