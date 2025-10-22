#include "Player.hpp"

Player::Player(float xPos, float yPos) : Entity(xPos, yPos)
{
	shape.setPosition(position);
	if (!texture.loadFromFile("Assets/Character/Astronaut_RunV2.png")) cout << "caca run" << endl << endl;
    if (!textureJump.loadFromFile("Assets/Character/Astronaut_JumpV2.png")) cout << "caca jump" << endl << endl;
    if (!textureJetpack.loadFromFile("Assets/Character/Astronaut_JetPack.png")) cout << "caca jump" << endl << endl;
	shape.setTexture(&texture);
	shape.setSize(Vector2f(CHARACTER_ASSET_SIZE, CHARACTER_ASSET_SIZE)); // donc 128x128 ici
	cout << "Joueur créé" << endl;
    stateMove = RUNNING;
    clockRun.start();
    staminaBarRect.setOutlineThickness(5.f);
    staminaBarRect.setOutlineColor(Color::White);
}

Player::~Player()
{
	cout << "Joueur détruit" << endl;
}

void Player::playerMovement(float deltaTime, Map& map)
{
	position.x = 0;

    if (!collision(map)) {
        velocity.y += gravity * deltaTime;
    }
    else {
        stateMove = RUNNING;
        if (jetpackStamina < 100) {
            jetpackStamina++;
        }
    }

    if (Keyboard::isKeyPressed(Keyboard::Key::Space)) {
        clockJump.start();
        jump(deltaTime);
    }

	position.y = velocity.y;
	shape.move(position);
}

bool Player::collision(Map& map)
{
    if (shape.getGlobalBounds().findIntersection(map.getBounds())) {
        velocity.y = 0;
        state = GROUNDED;
        return true;
    }
}

void Player::jump(float deltaTime)
{
    if (state == GROUNDED) {  // Sauter uniquement si le joueur est sur le sol / saute pas
        //sound.setBuffer(bufferJump);
        //if (sound.getStatus() != sf::Sound::Playing) {
        //    sound.play();
        //}
        state = JUMP;
        stateMove = JUMPING;
        velocity.y = -JUMP_FORCE; // Appliquer une force initiale vers le haut pour sauter 
        clockSecondJump.restart();
    }
    else if (clockSecondJump.getElapsedTime().asMilliseconds() >= 300 && state != GROUNDED && jetpackStamina >= 1.f) { // compteur permettant de savoir si on peut faire un deuxième saut
        //sound.setBuffer(bufferDoubleJump);
        //if (sound.getStatus() != sf::Sound::Playing) {
        //    sound.play();
        //}
        stateMove = JETPACKING;
        velocity.y = -JETPACK_FORCE;
        jetpackStamina--;
    }
}

void Player::animationManager(float deltaTime)
{
    switch (stateMove)
    {
    case RUNNING:
        shape.setTexture(&texture);
        animRun.y = 0; // reset le cycle d'anim sur y car on a pas d'anim sur l'axe y

        if (clockRun.getElapsedTime().asMilliseconds() > 55) { // horloge qui permet de modifier la vitesse d'anim
            animRun.x++; // on met +1 a notre anim donc change de "case"
            clockRun.restart(); // on restart la clock pour continuer
        }
        if (animRun.x > 5) // si on atteint la "fin de l'image" (la fin des "cases")
            animRun.x = 0; // on reset l'image et on recommence
        shape.setTextureRect(sf::IntRect({ animRun.x * CHARACTER_ASSET_SIZE, animRun.y * CHARACTER_ASSET_SIZE }, { CHARACTER_ASSET_SIZE, CHARACTER_ASSET_SIZE })); // on set le rect pour prendre que le 120x80
        break;
        
    case JUMPING:
        shape.setTexture(&textureJump);
        animJump.y = 0;

        if (clockJump.getElapsedTime().asMilliseconds() > 45) {
            animJump.x++;
            clockJump.restart();
        }
        if (animJump.x > 5)
            animJump.x = 0;
        shape.setTextureRect(IntRect({ animJump.x * CHARACTER_ASSET_SIZE, animJump.y * CHARACTER_ASSET_SIZE }, { CHARACTER_ASSET_SIZE, CHARACTER_ASSET_SIZE }));
        break;
    case JETPACKING:
        shape.setTexture(&textureJetpack);
        animJetpack.y = 0;

        if (clockJetpack.getElapsedTime().asMilliseconds() > 45) {
            animJetpack.x++;
            clockJetpack.restart();
        }
        if (animJetpack.x > 1)
            animJetpack.x = 0;
        shape.setTextureRect(IntRect({ animJetpack.x * CHARACTER_ASSET_SIZE, animJetpack.y * CHARACTER_ASSET_SIZE }, { CHARACTER_ASSET_SIZE, CHARACTER_ASSET_SIZE }));
        break;
    }
}

void Player::jetpackStaminaGestion()
{
    if (jetpackStamina >= 60) {
        staminaBar.setFillColor(Color::Green);
    }
    else if (jetpackStamina < 30) {
        staminaBar.setFillColor(Color::Red);
    }
    else if (jetpackStamina < 60) {
        staminaBar.setFillColor(Color::Yellow);
    }
    staminaBar.setSize(Vector2f(jetpackStamina, 10));
    staminaBar.setPosition(Vector2f(shape.getPosition().x + 10, shape.getPosition().y - 30));
    staminaBarRect.setSize(Vector2f(100, 10));
    staminaBarRect.setPosition(Vector2f(shape.getPosition().x + 10, shape.getPosition().y - 30));
}

void Player::update(float deltaTime, Map& map)
{
	playerMovement(deltaTime, map);
    animationManager(deltaTime);
    jetpackStaminaGestion();
}

void Player::draw(RenderWindow& window)
{
    window.draw(staminaBarRect);
    window.draw(staminaBar);
	window.draw(shape);
}