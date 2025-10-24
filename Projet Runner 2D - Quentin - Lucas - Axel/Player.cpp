#include "Player.hpp"

Player::Player() : sound(bufferRun), Entity()
{
    /* CHANGER LES NOMS DES FICHIERS POUR RESPECTER WILLIAM
       
    */

    // initialisation de tout
    //clockRun.start();
    //clockJump.start();
    //clockJetpack.start();
    //clockSecondJump.start();

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
    shape.setTexture(&texture);


    // préparation de la staminaBar pour le jetpack
    staminaBarRect.setOutlineThickness(5.f);
    staminaBarRect.setOutlineColor(Color::White);

    shape.setPosition(Vector2f(STGS::WIDTH * 0.05, STGS::HEIGHT - shape.getSize().y - STGS::HEIGHT / 10));

    // initialisation des sons
    if (!bufferRun.loadFromFile("Assets/SoundEffects/run.wav")) cout << "caca son run" << endl << endl;
    if (!bufferJump.loadFromFile("Assets/SoundEffects/jump.wav")) cout << "caca son jump" << endl << endl;
    if (!bufferJetpack.loadFromFile("Assets/SoundEffects/jetpack.wav")) cout << "caca son jetpack" << endl << endl;
    if (!bufferRunGravel.loadFromFile("Assets/SoundEffects/runGravel.wav")) cout << "caca son runGravel" << endl << endl;
}

Player::~Player() {}

bool Player::collision(Map& map)
{
    const std::vector<Obstacle*>& vectObs = map.getVectObs();
    const std::vector<Collectible*>& vectCollectible = map.getCollectible();

    for (auto it = vectObs.begin(); it != vectObs.end(); ++it) {
        auto& obstacle = *it;
        if (getFeetBounds().findIntersection(obstacle->getSafePlaceBounds())) {
            velocity.y = 0;
            state = GROUNDED;
            return true;
        }
        if (!isInvincible && getFeetBounds().findIntersection(obstacle->shape.getGlobalBounds())) {
            setLessLife();
            isInvincible = true;
            clockInvincible.restart();
            map.removeObstacle(obstacle);
            return true;
        } 
    }
    if (getFeetBounds().findIntersection(map.getBounds()) || getFeetBounds().findIntersection(map.getBounds2())) {
        velocity.y = 0;
        state = GROUNDED;
        return true;
    }
    for (auto& collectible : vectCollectible) {
        if (shape.getGlobalBounds().findIntersection(collectible->shape.getGlobalBounds())) {
            pessos++;
            map.removeCollectible(collectible);
            return true;
        }
    }
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
	shape.move(position);
}

void Player::jump(float deltaTime)
{
    if (state == GROUNDED) {  // Sauter uniquement si le joueur est sur le sol / saute pas
        state = JUMP;
        stateMove = JUMPING;
        velocity.y = -JUMP_FORCE; // Appliquer une force initiale vers le haut pour sauter 
        clockSecondJump.restart();
    }
    else if (clockSecondJump.getElapsedTime().asMilliseconds() >= 300 && state != GROUNDED && jetpackStamina >= 1.f) { // compteur permettant de savoir si on peut faire un deuxième saut
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
        soundManager(bufferRun);
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
        soundManager(bufferJump);
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
        soundManager(bufferJetpack);
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

void Player::invincibility()
{
    if (clockInvincible.getElapsedTime().asSeconds() >= 2) {
        clockInvincible.stop();
        isInvincible = false;
    }

    if (isInvincible) {
        // ici, on transforme notre clock invisible en int pour utiliser % qui ne marche pas bien sur les floats
        // donc ca fais 1,2,3 au lieu de 100 ms, 200 ms etc et le % 2 va faire 0,1,0,1,0,1
        if (((int)(clockInvincible.getElapsedTime().asMilliseconds() / 100)) % 2 == 0)
            shape.setFillColor(Color(255, 255, 255, 0));
        else
            shape.setFillColor(Color::White); 
    }
    else {
        shape.setFillColor(Color::White);
    }
}

FloatRect Player::getFeetBounds() const
{
    FloatRect bounds = shape.getGlobalBounds();
    float feet = bounds.size.y * 0.1f;

    Vector2f feetPos(bounds.position.x, bounds.position.y + bounds.size.y - feet);

    Vector2f feetSize(bounds.size.x, feet);

    return FloatRect(feetPos, feetSize);
}

int Player::getLife()
{
    return life;
}

void Player::setLife(int l)
{
    life = l;
}

void Player::setLessLife()
{
    if (life <= 0) {
        life = 0;
    }
    else {
        life--;
    }
    cout << life << endl;
}

void Player::setUpLife()
{
    if (life >= 3) {
        life = 3;
    }
    else {
        life++;
    }
}

int Player::getPessos()
{
    return pessos;
}

void Player::soundManager(SoundBuffer& buffer)
{
    const sf::SoundBuffer& currentBuffer = sound.getBuffer();

    if (&currentBuffer != &buffer && life != 0)
    {
        sound.stop();
        sound.setBuffer(buffer);

        if (&buffer == &bufferJump)
            sound.setLooping(false);
        else
            sound.setLooping(true);

        sound.setVolume(volumeSound);
        sound.play();
    }
    else if (sound.getStatus() != sf::SoundSource::Status::Playing && life != 0)
    {
        sound.play();
    }
}

void Player::update(float deltaTime, Map& map)
{
    if (life != 0) {
        invincibility();
        playerMovement(deltaTime, map);
        animationManager(deltaTime);
        jetpackStaminaGestion();
    }
}

void Player::draw(RenderWindow& window)
{
    if (life != 0) {
        window.draw(staminaBarRect);
        window.draw(staminaBar);
        window.draw(shape);
    }
}