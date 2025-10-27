#include "Player.hpp"

Player::Player() : sound(bufferRun), soundCoin(bufferCoin), soundDeath(bufferHurt) {
    //CHANGER LES NOMS DES FICHIERS POUR RESPECTER WILLIAM
    //
    // buffer dans asset manager
    // collision glissade
}

Player::~Player() {}

bool Player::collision(Map& map) {
    const std::vector<Obstacle*>& vectObs = map.getVectObs();
    const std::vector<Collectible*>& vectCollectible = map.getCollectible();
    const std::vector<Plateform*>& vectPlat = map.getPlateform();

    for (auto it = vectObs.begin(); it != vectObs.end(); ++it) {
        auto& obstacle = *it;
        if (getFeetBounds().findIntersection(obstacle->getSafePlaceBounds())) {
            velocity.y = 0;
            state = GROUNDED;
            stateMove = PLATEFORMING;
            return true;
        }
        if (!isInvincible && shape.getGlobalBounds().findIntersection(obstacle->shape.getGlobalBounds())) {
            setLessLife();
            isInvincible = true;
            clockInvincible.restart();
            map.removeObstacle(obstacle);
            soundDeath.play();
            takeDamageBool = true;
            takeDamageClock.restart();
            return true;
        } 
    }
    for (auto& collectible : vectCollectible) {
        if (shape.getGlobalBounds().findIntersection(collectible->getShape().getGlobalBounds())) {
            pessos++;
            map.removeCollectible(collectible);
            soundCoin.play();
            return true;
        }
    }
    for (auto it = vectPlat.begin(); it != vectPlat.end(); ++it) {
        auto& plateform = *it;
        if (getFeetBounds().findIntersection(plateform->shape.getGlobalBounds())) {
            velocity.y = 0;
            state = GROUNDED;
            stateMove = PLATEFORMING;
            return true;
        }
    }
    if (getFeetBounds().findIntersection(map.getBounds()) || getFeetBounds().findIntersection(map.getBounds2())) {
        velocity.y = 0;
        state = GROUNDED;
        stateMove = RUNNING;
        return true;
    }
    return false;
}

void Player::initPlayer()
{
    velocity = { 0, 0 };
    position = { 0,0 };
    state = NOTHING;
    stateMove = NONE;
    jetpackStamina = 100;
    animRun = { 0,0 };
    animJump = { 0,0 };
    animJetpack = { 0,0 };

    sound.setVolume(volumeSound);
    soundCoin.setVolume(volumeSound);
    soundDeath.setVolume(volumeSound);

    // chargement des textures

    // setSmooth pour des images plus nette 
    Shared::playerJumpTexture.setSmooth(true);
    Shared::playerJetpackTexture.setSmooth(true);

    shape.setSize(sf::Vector2f(static_cast<float>(CHARACTER_ASSET_SIZE),
        static_cast<float>(CHARACTER_ASSET_SIZE)));

    shape.setTexture(&Shared::playerTexture);

    // préparation de la staminaBar pour le jetpack
    staminaBarRect.setOutlineThickness(5.f);
    staminaBarRect.setOutlineColor(sf::Color::White);

    shape.setPosition(sf::Vector2f(STGS::WIDTH * 0.05, STGS::HEIGHT - shape.getSize().y - STGS::HEIGHT / 10));

    // initialisation des sons
    if (!bufferRun.loadFromFile("Assets/SoundEffects/run.wav")) std::cout << "caca son run" << std::endl << std::endl;
    if (!bufferJump.loadFromFile("Assets/SoundEffects/jump.wav")) std::cout << "caca son jump" << std::endl << std::endl;
    if (!bufferJetpack.loadFromFile("Assets/SoundEffects/jetpack.wav")) std::cout << "caca son jetpack" << std::endl << std::endl;
    if (!bufferRunGravel.loadFromFile("Assets/SoundEffects/runGravel2.wav")) std::cout << "caca son runGravel" << std::endl << std::endl;

    if (!bufferCoin.loadFromFile("Assets/SoundEffects/coin.wav")) std::cout << "caca son coin" << std::endl << std::endl;
    if (!bufferHurt.loadFromFile("Assets/SoundEffects/oof.wav")) std::cout << "caca son oof" << std::endl << std::endl;
    if (!bufferSlide.loadFromFile("Assets/SoundEffects/slide.wav")) std::cout << "caca son slide" << std::endl << std::endl;

    isInvincible = false;
    takeDamageBool = false;

    float w = static_cast<float>(STGS::WIDTH);
    float h = static_cast<float>(STGS::HEIGHT);
    float border = 50.f;

    sf::Color redOpaque(255, 0, 0, 180);
    sf::Color redTransparent(255, 0, 0, 0);

    takeDamageLeft[0] = sf::Vertex({ 0.f, 0.f }, redOpaque);
    takeDamageLeft[1] = sf::Vertex({ border, 0.f }, redTransparent);
    takeDamageLeft[2] = sf::Vertex({ border, h }, redTransparent);
    takeDamageLeft[3] = sf::Vertex({ 0.f, h }, redOpaque);

    takeDamageRight[0] = sf::Vertex({ w - border, 0.f }, redTransparent);
    takeDamageRight[1] = sf::Vertex({ w, 0.f }, redOpaque);
    takeDamageRight[2] = sf::Vertex({ w, h }, redOpaque);
    takeDamageRight[3] = sf::Vertex({ w - border, h }, redTransparent);

    takeDamageTop[0] = sf::Vertex({ 0.f, 0.f }, redOpaque);
    takeDamageTop[1] = sf::Vertex({ w, 0.f }, redOpaque);
    takeDamageTop[2] = sf::Vertex({ w, border }, redTransparent);
    takeDamageTop[3] = sf::Vertex({ 0.f, border }, redTransparent);

    takeDamageBottom[0] = sf::Vertex({ 0.f, h - border }, redTransparent);
    takeDamageBottom[1] = sf::Vertex({ w, h - border }, redTransparent);
    takeDamageBottom[2] = sf::Vertex({ w, h }, redOpaque);
    takeDamageBottom[3] = sf::Vertex({ 0.f, h }, redOpaque);
}

void Player::playerMovement(float deltaTime, Map& map) {
    if (!collision(map)) 
        velocity.y += gravity * deltaTime;
    else if (collision(map) && stateMove == PLATEFORMING) {
        if (jetpackStamina < 100) 
            jetpackStamina++;
    }
    else {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            stateMove = SLIDING;
        }
        else {
            stateMove = RUNNING;
        }
        if (jetpackStamina < 100)
            jetpackStamina++;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) 
        jump(deltaTime);

	position.y = velocity.y;
	shape.move(position);
}

void Player::jump(float deltaTime) {
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

void Player::animationManager(float deltaTime) {
    switch (stateMove) {
    case RUNNING:
        soundManager(bufferRun);
        shape.setTexture(&Shared::playerTexture);
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
        shape.setTexture(&Shared::playerJumpTexture);
        animJump.y = 0;

        if (clockJump.getElapsedTime().asMilliseconds() > 45) {
            animJump.x++;
            clockJump.restart();
        }
        if (animJump.x > 5)
            animJump.x = 0;
        shape.setTextureRect(sf::IntRect({ animJump.x * CHARACTER_ASSET_SIZE, animJump.y * CHARACTER_ASSET_SIZE }, { CHARACTER_ASSET_SIZE, CHARACTER_ASSET_SIZE }));
        break;
    case JETPACKING:
        soundManager(bufferJetpack);
        shape.setTexture(&Shared::playerJetpackTexture);
        animJetpack.y = 0;

        if (clockJetpack.getElapsedTime().asMilliseconds() > 45) {
            animJetpack.x++;
            clockJetpack.restart();
        }
        if (animJetpack.x > 1)
            animJetpack.x = 0;
        shape.setTextureRect(sf::IntRect({ animJetpack.x * CHARACTER_ASSET_SIZE, animJetpack.y * CHARACTER_ASSET_SIZE }, { CHARACTER_ASSET_SIZE, CHARACTER_ASSET_SIZE }));
        break;
    case PLATEFORMING:
        soundManager(bufferRunGravel);
        shape.setTexture(&Shared::playerTexture);
        animRun.y = 0; // reset le cycle d'anim sur y car on a pas d'anim sur l'axe y

        if (clockRun.getElapsedTime().asMilliseconds() > 55) { // horloge qui permet de modifier la vitesse d'anim
            animRun.x++; // on met +1 a notre anim donc change de "case"
            clockRun.restart(); // on restart la clock pour continuer
        }
        if (animRun.x > 5) // si on atteint la "fin de l'image" (la fin des "cases")
            animRun.x = 0; // on reset l'image et on recommence
        shape.setTextureRect(sf::IntRect({ animRun.x * CHARACTER_ASSET_SIZE, animRun.y * CHARACTER_ASSET_SIZE }, { CHARACTER_ASSET_SIZE, CHARACTER_ASSET_SIZE })); // on set le rect pour prendre que le 120x80
        break;
    case SLIDING:
        soundManager(bufferSlide);
        shape.setTexture(&Shared::playerSlideTexture);
        shape.setTextureRect(sf::IntRect({ 0, 0 }, { 128, 128 })); // on set le rect pour prendre que le 120x80
        break;
    }
}

void Player::jetpackStaminaGestion() {
    if (jetpackStamina >= 60)
        staminaBar.setFillColor(sf::Color::Green);
    else if (jetpackStamina < 30) 
        staminaBar.setFillColor(sf::Color::Red);
    else if (jetpackStamina < 60) 
        staminaBar.setFillColor(sf::Color::Yellow);

    staminaBar.setSize(sf::Vector2f(jetpackStamina, 10));
    staminaBar.setPosition(sf::Vector2f(shape.getPosition().x + 10, shape.getPosition().y - 30));
    staminaBarRect.setSize(sf::Vector2f(100, 10));
    staminaBarRect.setPosition(sf::Vector2f(shape.getPosition().x + 10, shape.getPosition().y - 30));
}

void Player::invincibility() {
    if (clockInvincible.getElapsedTime().asSeconds() >= 2) {
        clockInvincible.stop();
        isInvincible = false;
    }

    if (isInvincible) {
        // ici, on transforme notre clock invisible en int pour utiliser % qui ne marche pas bien sur les floats
        // donc ca fais 1,2,3 au lieu de 100 ms, 200 ms etc et le % 2 va faire 0,1,0,1,0,1
        if (((int)(clockInvincible.getElapsedTime().asMilliseconds() / 100)) % 2 == 0)
            shape.setFillColor(sf::Color(255, 255, 255, 0));
        else
            shape.setFillColor(sf::Color::White);
    }
    else
        shape.setFillColor(sf::Color::White);
}

void Player::soundManager(sf::SoundBuffer& buffer) {
    const sf::SoundBuffer& currentBuffer = sound.getBuffer();

    if (&currentBuffer != &buffer && life != 0) {
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
        sound.play();
}

void Player::update(float deltaTime, Map& map) {
    if (life != 0) {
        invincibility();
        animationTakeDamage();
        playerMovement(deltaTime, map);
        animationManager(deltaTime);
        jetpackStaminaGestion();
    }
}

void Player::draw(sf::RenderWindow& window) {
    if (life != 0) {
        window.draw(staminaBarRect);
        window.draw(staminaBar);
        window.draw(shape);
    }

    if (takeDamageBool) {
        window.draw(takeDamageLeft, 4, sf::PrimitiveType::TriangleFan);
        window.draw(takeDamageRight, 4, sf::PrimitiveType::TriangleFan);
        window.draw(takeDamageTop, 4, sf::PrimitiveType::TriangleFan);
        window.draw(takeDamageBottom, 4, sf::PrimitiveType::TriangleFan);
    }
   
}

sf::FloatRect Player::getFeetBounds() const {
    sf::FloatRect bounds = shape.getGlobalBounds();
    float feet = bounds.size.y * 0.1f;
    sf::Vector2f feetPos(bounds.position.x, bounds.position.y + bounds.size.y - feet);
    sf::Vector2f feetSize(bounds.size.x, feet);
    return sf::FloatRect(feetPos, feetSize);
}

void Player::setLessLife() {
    if (life <= 0) 
        life = 0;
    else 
        life--;
}

void Player::setUpLife() {
    if (life >= 3) 
        life = 3;
    else 
        life++;
}

int Player::getLife() { return life; }
void Player::setLife(int l) { life = l; }
int Player::getPessos() {  return pessos; }

void Player::animationTakeDamage() {
    if (takeDamageClock.getElapsedTime().asSeconds() >= 2.f) {
        takeDamageClock.stop();
        takeDamageBool = false;
        return;
    }
    if (!takeDamageBool)
        return;
}
