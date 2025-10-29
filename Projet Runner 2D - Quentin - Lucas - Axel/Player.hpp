#pragma once

#include "Map.hpp"

class Shop;

class Player {
public :
	Player();
	~Player();

	void initPlayer();
	void playerMovement(float deltaTime, Map& map, int& pessos);
	void jump(float deltaTime);
	bool collision(Map& map, int& pessos);
	void animationManager(float deltaTime); 
	void staminaGestion();
	void invincibility(Shop& shop);
	void animationTakeDamage();
	void soundManager(sf::SoundBuffer& buffer);
	void stopSounds();
	void update(float deltaTime, Map& map, int& pessos, Shop& shop);
	void draw(sf::RenderWindow& window);

	//getters/setters
	sf::FloatRect getFeetBounds() const;
	sf::FloatRect getSlideBounds() const;
	int getLife();
	void setLife(int l);
	void setLessLife();
	void setUpLife();
	int getVolume();
	void setVolumeLess();
	void setVolumeUp();
	void setVolume(int sound);

	enum State { NOTHING, GROUNDED, JUMP };
	State state;

	enum MoveState { NONE, RUNNING, JUMPING, JETPACKING, PLATEFORMING, SLIDING };
	MoveState stateMove;

private : 
	sf::RectangleShape shape;
	sf::RectangleShape jetpackStaminaBar; // barre d'endurance du jetpack
	sf::RectangleShape jetpackStaminaBarRect; // outline de la barre d'endurance du jetpack maximale
	sf::RectangleShape slideStaminaBar;
	sf::RectangleShape slideStaminaBarRect; 
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

	sf::Sound sound;
	sf::Sound soundCoin;
	sf::Sound soundDeath;
	sf::Sound soundJohnCena;

	sf::Vector2f position;
	sf::Vector2f velocity;

	const float JUMP_FORCE = 1800.f; // force initiale du saut // 40
	const float JETPACK_FORCE = 900.f; // force de propulsion du jetpack // 15
	const int CHARACTER_ASSET_SIZE = 128; // taille du character
	float jetpackStamina = 100.f; // endurance du jetpack
	float slideStamina = 100.f; // durée de la glissade
	float slideStaminaMax = 100.f; // maximum de la glissade
	bool isReloadSlideBar = false; // recharge de glissade
	int volumeSound = 50; // son 
	int life = 3;
	bool isInvincible = false;
	const float gravity = 5000.0f; // 150
	bool takeDamageBool = false;
};