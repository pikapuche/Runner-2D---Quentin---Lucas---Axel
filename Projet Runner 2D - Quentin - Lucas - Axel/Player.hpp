#pragma once

#include "Map.hpp"

class Player {
public :
	Player();
	~Player();

	void initPlayer();
	void playerMovement(float deltaTime, Map& map);
	void jump(float deltaTime);
	bool collision(Map& map);
	void animationManager(float deltaTime); 
	void jetpackStaminaGestion();
	void invincibility();
	void animationTakeDamage();
	void soundManager(sf::SoundBuffer& buffer);
	void update(float deltaTime, Map& map);
	void draw(sf::RenderWindow& window);

	//getters/setters
	sf::FloatRect getFeetBounds() const;
	int getLife();
	void setLife(int l);
	void setLessLife();
	void setUpLife();
	int getPessos();

	enum State { NOTHING, GROUNDED, JUMP };
	State state;

	enum MoveState { NONE, RUNNING, JUMPING, JETPACKING, PLATEFORMING, SLIDING };
	MoveState stateMove;

private : 
	sf::RectangleShape shape;
	sf::RectangleShape staminaBar; // barre d'endurance du jetpack
	sf::RectangleShape staminaBarRect; // outline de la barre d'endurance du jetpack maximale
	sf::Vertex takeDamageLeft[4], takeDamageRight[4], takeDamageTop[4], takeDamageBottom[4];

	sf::Clock clockRun; // Clock qui permet de modifier la vitesse d'anim
	sf::Clock clockJump; // Clock qui permet de modifier la vitesse d'anim
	sf::Clock clockSecondJump; // Clock qui permet de modifier le temps entre le premier et le deuxieme saut
	sf::Clock clockJetpack; // Clock quand on est pour l'anim jetpack
	sf::Clock clockInvincible; // Clock qui permet de timer l'invincibilité
	sf::Clock takeDamageClock;

	sf::Vector2i animRun;
	sf::Vector2i animJump;
	sf::Vector2i animJetpack;

	sf::SoundBuffer bufferRunGravel; // son quand le perso va courir
	sf::SoundBuffer bufferRun; // son quand le perso va courir
	sf::SoundBuffer bufferJump; // son quand le perso va sauter
	sf::SoundBuffer bufferJetpack; // son quand le perso va utiliser le jetpack
	sf::SoundBuffer bufferCoin;
	sf::SoundBuffer bufferHurt;
	sf::SoundBuffer bufferSlide;

	sf::Sound sound;
	sf::Sound soundCoin;
	sf::Sound soundDeath;

	sf::Vector2f position;
	sf::Vector2f velocity;

	const float JUMP_FORCE = 40.f; // force initiale du saut
	const float JETPACK_FORCE = 15.f; // force de propulsion du jetpack
	const int CHARACTER_ASSET_SIZE = 128; // taille du character
	float jetpackStamina = 100.f; // endurance du jetpack
	int volumeSound = 100;
	int life = 3;
	int pessos = 0;
	bool isInvincible;
	const float gravity = 150.0f;
	bool takeDamageBool;
};