#pragma once

/////////////////////////////////
/// Header
////////////////////////////////
#include "Map.hpp"

class Shop;

class Player {
public :

#pragma region Functions
	/////////////////////////////////
	/// \brief Constructor
	////////////////////////////////
	Player();
	/////////////////////////////////
	/// \brief Destructor
	////////////////////////////////
	~Player();

	/////////////////////////////////
	/// \brief function for initialisation Player class
	///
	/// \param volumeSound  The sound of the sounds effects of the player
	////////////////////////////////
	void initPlayer(int& volumeSound);
	/////////////////////////////////
	/// \brief function for manage movement of the player
	///
	/// \param deltaTime  Time in the game for equalize movement
	/// \param map  Map for get the bounds of elements inside for collisions
	/// \param coins  Coins for get their bounds for collisions
	////////////////////////////////
	void playerMovement(float deltaTime, Map& map, int& pessos);
	/////////////////////////////////
	/// \brief function for manage the jmup of the player
	///
	/// \param deltaTime  Time in the game for equalize movement
	////////////////////////////////
	void jump(float deltaTime);
	/////////////////////////////////
	/// \brief function for manage the jmup of the player
	///
	/// \param map  Map for get the bounds of elements inside for collisions
	/// \param coins  Coins for get their bounds for collisions
	////////////////////////////////
	bool collision(Map& map, int& pessos);
	/////////////////////////////////
	/// \brief function for manage the animation of the player
	///
	/// \param deltaTime  Time in the game for equalize movement
	////////////////////////////////
	void animationManager(float deltaTime); 
	/////////////////////////////////
	/// \brief function for manage the stamina of the jetpack and the slide of the player
	////////////////////////////////
	void staminaGestion();
	/////////////////////////////////
	/// \brief function for manage the invincibility of the player when he takes damages
	///
	/// \param shop  Use for the invincibility reset for any skin buy in the shop
	////////////////////////////////
	void invincibility(Shop& shop);
	/////////////////////////////////
	/// \brief function for manage the blinking of the player when he takes damages
	////////////////////////////////
	void BlinkingWhenDamage();
	/////////////////////////////////
	/// \brief function for manage the sounds effects
	///
	/// \param buffer  Use for get which buffer is active and replace it or not by the new one
	////////////////////////////////
	void soundManager(sf::SoundBuffer& buffer);
	/////////////////////////////////
	/// \brief function for stop all the sounds effects
	////////////////////////////////
	void stopSounds();
	/////////////////////////////////
	/// \brief function for manage the blinking of the player when he takes damages
	///
	/// \param deltaTime  Time in the game for equalize movement
	/// \param map  Map for get the bounds of elements inside for collisions
	/// \param coins  Coins for get their bounds for collisions
	/// \param shop  Use for the invincibility reset for any skin buy in the shop
	////////////////////////////////
	void update(float deltaTime, Map& map, int& pessos, Shop& shop);
	/////////////////////////////////
	/// \brief function for draw the player and a part of his HUD
	/// 
	/// \param window  for get the window of the game and draw the element of the player 
	////////////////////////////////
	void draw(sf::RenderWindow& window);
#pragma endregion Functions

#pragma region Getters / Setters

	/////////////////////////////////
	/// \brief getter for the bounds of the feet player (for better / realistic collision)
	////////////////////////////////
	sf::FloatRect getFeetBounds() const;

	/////////////////////////////////
	/// \brief getter for the bounds when the player is sliding (for better / realistic collision)
	////////////////////////////////
	sf::FloatRect getSlideBounds() const;

	/////////////////////////////////
	/// \brief getter for the life of the player
	////////////////////////////////
	int getLife();

	/////////////////////////////////
	/// \brief setter for the life of the player (choose the number you need)
	////////////////////////////////
	void setLife(int l);

	/////////////////////////////////
	/// \brief setter for the life of the player (put -1 to currently life)
	////////////////////////////////
	void setLessLife();

	/////////////////////////////////
	/// \brief setter for the life of the player (put +1 to currently life)
	////////////////////////////////
	void setUpLife();
#pragma endregion Getters / Setters

#pragma region Enums
	/////////////////////////////////
	/// \brief enum for the state of the player to know if he is GROUNDED or not
	////////////////////////////////
	enum State { NOTHING, GROUNDED, JUMP };
	State state;

	/////////////////////////////////
	/// \brief enum for know the actions of the player for animations
	////////////////////////////////
	enum MoveState { NONE, RUNNING, JUMPING, JETPACKING, PLATEFORMING, SLIDING };
	MoveState stateMove;
#pragma endregion Enums

private : 

#pragma region RectangleShape

	/////////////////////////////////
	/// \brief principal shape for the player
	////////////////////////////////
	sf::RectangleShape shape;

	/////////////////////////////////
	/// \brief shape for the jetpack bar who get less bigger if use
	////////////////////////////////
	sf::RectangleShape jetpackStaminaBar;

	/////////////////////////////////
	/// \brief shape for the background of the jetpack bar 
	////////////////////////////////	
	sf::RectangleShape jetpackStaminaBarRect;

	/////////////////////////////////
	/// \brief shape for the slide stamina who get less bigger if use
	////////////////////////////////
	sf::RectangleShape slideStaminaBar;

	/////////////////////////////////
	/// \brief shape for the background of the slide bar
	////////////////////////////////
	sf::RectangleShape slideStaminaBarRect; 
#pragma endregion RectangleShape

#pragma region Vertex
	/////////////////////////////////
	/// \brief vertex for the take damage of the player 
	////////////////////////////////
	sf::Vertex takeDamageLeft[4], takeDamageRight[4], takeDamageTop[4], takeDamageBottom[4];
#pragma endregion Vertex

#pragma region Clock
	/////////////////////////////////
	/// \brief clock for the control of the run anim 
	////////////////////////////////
	sf::Clock clockRun; 

	/////////////////////////////////
	/// \brief clock for the control of the jump anim 
	////////////////////////////////
	sf::Clock clockJump; 

	/////////////////////////////////
	/// \brief clock for the control of the timing for do the second jump and activate jetpack 
	////////////////////////////////
	sf::Clock clockSecondJump;

	/////////////////////////////////
	/// \brief clock for the control of the jetpack anim 
	////////////////////////////////
	sf::Clock clockJetpack; 

	/////////////////////////////////
	/// \brief clock for the control of the invincibility state
	////////////////////////////////
	sf::Clock clockInvincible; 

	/////////////////////////////////
	/// \brief clock for the control of the run anim 
	////////////////////////////////
	sf::Clock takeDamageClock;
#pragma endregion Clock

#pragma region Vector2f
	sf::Vector2f position;
	sf::Vector2f velocity;
#pragma endregion Vector2f

#pragma region Vector2i
	sf::Vector2i animRun;
	sf::Vector2i animJump;
	sf::Vector2i animJetpack;
#pragma endregion Vector2i

#pragma region Sound
	sf::Sound sound;
	sf::Sound soundCoin;
	sf::Sound soundDeath;
	sf::Sound soundJohnCena;
#pragma endregion Sound

#pragma region float values
	const float JUMP_FORCE = 1800.f; // force initiale du saut // 40
	const float JETPACK_FORCE = 900.f; // force de propulsion du jetpack // 15
	const float gravity = 5000.0f; // 150
	
	float jetpackStamina = 100.f; // endurance du jetpack
	float slideStamina = 100.f; // durée de la glissade
	float slideStaminaMax = 100.f; // maximum de la glissade
#pragma endregion float values

#pragma region int values
	const int CHARACTER_ASSET_SIZE = 128; // taille du character
	int life = 3;
#pragma endregion bool values

#pragma region bool values
	bool isReloadSlideBar = false; // recharge de glissade
	bool isInvincible = false;
	bool takeDamageBool = false;
#pragma endregion bool values
};