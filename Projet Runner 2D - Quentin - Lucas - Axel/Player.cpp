#include "Player.hpp"

Player::Player(float xPos, float yPos) : Entity(xPos, yPos)
{
	shape.setPosition(position);
	if (!texture.loadFromFile("Assets/Character/_Run.png")) cout << "prout" << endl << endl << endl << endl; // 120x80 pour une case
	shape.setTexture(&texture);
	shape.setSize(Vector2f(120, 80)); // donc 120x80 ici
	shape.setScale(Vector2f(3, 3)); // et ici on peut l'agrandir
	cout << "Joueur créé" << endl;
    stateMove = RUNNING;
    runClock.start();
}

Player::~Player()
{
	cout << "Joueur détruit" << endl;
}

void Player::playerMovement(float deltaTime)
{
	position.x = 0;

	velocity.y = gravity * deltaTime;
    if (Keyboard::isKeyPressed(Keyboard::Key::Space)) {
        //jump();
        velocity.y = -JUMP_FORCE;
    }
	position.y = velocity.y * deltaTime;
	shape.move(position);
}

void Player::jump()
{
    if (state == GROUNDED) {  // Sauter uniquement si le joueur est sur le sol / saute pas
        //sound.setBuffer(bufferJump);
        //if (sound.getStatus() != sf::Sound::Playing) {
        //    sound.play();
        //}
        state = JUMP;
        stateMove = JUMPING;
        velocity.y = -JUMP_FORCE;  // Appliquer une force initiale vers le haut pour sauter 
        jumpCount = 1;
        jumpClock.restart();
    }
    else if (jumpCount == 1 && jumpClock.getElapsedTime().asMilliseconds() >= 300 && state != GROUNDED) { // compteur permettant de savoir si on peut faire un deuxième saut
        //sound.setBuffer(bufferDoubleJump);
        //if (sound.getStatus() != sf::Sound::Playing) {
        //    sound.play();
        //}
        velocity.y = -JUMP_FORCE;
        jumpCount = 2;
    }
}

void Player::animationManager(float deltaTime)
{
    switch (stateMove)
    {
    case RUNNING:
        anim_run.y = 0; // reset le cycle d'anim sur y car on a pas d'anim sur l'axe y

        if (runClock.getElapsedTime().asMilliseconds() > 55) { // horloge qui permet de modifier la vitesse d'anim

            anim_run.x++; // on met +1 a notre anim donc change de "case"
            runClock.restart(); // on restart la clock pour continuer
        }
        if (anim_run.x > 9) {// si on atteint la "fin de l'image" (la fin des "cases")
            anim_run.x = 0; // on reset l'image et on recommence
        }

        shape.setTextureRect(sf::IntRect({ anim_run.x * 120, anim_run.y * 80 }, { 120, 80 })); // on set le rect pour prendre que le 120x80

        break;
        /*
    case JUMPING:
        animJumpTimeDecr += deltaTime;
        anim_jump.y = 0;
        if (animJumpTimeDecr > 0.12f) {
            anim_jump.x++;
            animJumpTimeDecr = 0;
        }
        if (anim_jump.x > 1)
            anim_jump.x = 0;
        shape.setTextureRect(IntRect({ anim_jump.x * 64, anim_jump.y * 64 }, { 64, 64 }));
        break;
    case DASHING:
        animJumpTimeDecr += deltaTime;
        anim_jump.y = 0;
        if (animJumpTimeDecr > 0.12f) {
            anim_jump.x++;
            animJumpTimeDecr = 0;
        }
        if (anim_jump.x > 1)
            anim_jump.x = 0;
        shape.setTextureRect(IntRect({ anim_jump.x * 64, anim_jump.y * 64 }, { 64, 64 }));
        break;
        */
    }
}
/*
void Player::dash(float deltaTime)
{
    if (isDashing) {
        sprite.setColor(Color::Blue);
        if (stateLook == LOOK_LEFT) {
            SPEED = 2000;
            position.x -= 2 + SPEED * deltaTime;
        }
        if (stateLook == LOOK_RIGHT) {
            SPEED = 2000;
            position.x += 2 + SPEED * deltaTime;
        }
        if (clock.getElapsedTime().asMilliseconds() >= 100) {
            isDashing = false;
            SPEED = 300.f;
            coolDownDash.restart();
        }
    }
    else {
        sprite.setColor(Color::White);
    }
}
*/
void Player::update(float deltaTime)
{
	playerMovement(deltaTime);
    animationManager(deltaTime);
}

void Player::draw(RenderWindow& window)
{
	window.draw(shape);
}
