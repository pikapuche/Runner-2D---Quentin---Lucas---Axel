#include "Player.hpp"

Player::Player() : soundRun(bufferRun), soundJump(bufferJump), soundJetpack(bufferJetpack), Entity()
{
    /* CHANGER LES NOMS DES FICHIERS POUR RESPECTER WILLIAM
       Collisions sur les trucs de la map
       Faire les différents sons
       Créer d'autres touches pour avoir certains bonus ?
       créer des ennemis ?
    */

    // initialisation de tout
    clockRun.start();
    clockJump.start();
    clockJetpack.start();
    clockSecondJump.start();

    velocity = { 0, 0 };
    position = { 0,0 };
    state = NOTHING;
    stateMove = NONE;
    jetpackStamina = 100;
    animRun = { 0,0 };
    animJump = { 0,0 };
    animJetpack = { 0,0 };

    // chargement des textures
	if (!texture.loadFromFile("Assets/Character/Astronaut_RunV2.png")) cout << "caca run" << endl << endl;
    if (!textureJump.loadFromFile("Assets/Character/Astronaut_JumpV2.png")) cout << "caca jump" << endl << endl;
    if (!textureJetpack.loadFromFile("Assets/Character/Astronaut_JetPack.png")) cout << "caca jetpack" << endl << endl;

    // setSmooth pour des images plus nette 
    textureJump.setSmooth(true);
    textureJetpack.setSmooth(true);

	shape.setSize(Vector2f(CHARACTER_ASSET_SIZE, CHARACTER_ASSET_SIZE)); // 128x128 car la size du perso est 128 px

    // préparation de la staminaBar pour le jetpack
    staminaBarRect.setOutlineThickness(5.f);
    staminaBarRect.setOutlineColor(Color::White);

    shape.setPosition(Vector2f(STGS::WIDTH * 0.05, STGS::HEIGHT - shape.getSize().y - STGS::HEIGHT / 10));

    // initialisation des sons
    if (!bufferRun.loadFromFile("Assets/SoundEffects/run.wav")) cout << "caca son run" << endl << endl;

    soundRun.setBuffer(bufferRun);
    soundRun.setLooping(true);
    soundRun.setVolume(volumeSound);

    soundJump.setBuffer(bufferJump);
    soundJump.setLooping(false);
    soundJump.setVolume(volumeSound);

    soundJetpack.setBuffer(bufferJetpack);
    soundJetpack.setLooping(true);
    soundJetpack.setVolume(volumeSound);
}

Player::~Player() {}

bool Player::collision(Map& map)
{
    const std::vector<Obstacle*>& vectObs = map.getVectObs();
    for (auto it = vectObs.begin(); it != vectObs.end(); ++it) {
        auto& obstacle = *it;
        if (shape.getGlobalBounds().findIntersection(obstacle->getSafePlaceBounds())) {
            velocity.y = 0;
            state = GROUNDED;
            return true;
        }
        if (shape.getGlobalBounds().findIntersection(map.getBounds())) {
            velocity.y = 0;
            state = GROUNDED;
            return true;
        }
    }
    soundRun.stop();
    return false;
}

void Player::playerMovement(float deltaTime, Map& map)
{
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
        jump(deltaTime);
    }

	position.y = velocity.y;
    if (shape.getPosition().y > 850) {
        shape.setPosition({ shape.getPosition().x, 850 });
    }
	shape.move(position);
}

void Player::jump(float deltaTime)
{
    if (state == GROUNDED) {  // Sauter uniquement si le joueur est sur le sol / saute pas
        //sound.setBuffer(bufferJump);
        //if (sound.getStatus() != sf::Sound::Playing) {
        //    sound.play();
        //}
        soundJump.play();
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
        soundJump.stop();
        soundJetpack.play();
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
        soundRun.setBuffer(bufferJump);
        soundRun.play();
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
        soundRun.setBuffer(bufferJetpack);
        soundRun.play();
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

void Player::soundManager()
{
    soundRun.play();
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