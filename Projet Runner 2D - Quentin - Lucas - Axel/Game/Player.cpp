#pragma once

#include "Player.hpp"
#include "../Menu/Shop.hpp" // ne pas toucher

Player::Player() : sound(Shared::bufferRun), soundCoin(Shared::bufferCoin), soundDeath(Shared::bufferHurt), soundJohnCena(Shared::bufferJohn) {

    // possible de faire pop 3 gros obstacle et le dernier en glissade pour obliger une glissade ?
}

Player::~Player() {}

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
    life = 3;
    sound.setVolume(volumeSound);
    soundCoin.setVolume(volumeSound);
    soundDeath.setVolume(volumeSound);
    soundJohnCena.setBuffer(Shared::bufferJohn);
    soundJohnCena.setVolume(volumeSound);

    // chargement des textures

    // setSmooth pour des images plus nette 
    Shared::playerJumpTexture.setSmooth(true);
    Shared::playerJetpackTexture.setSmooth(true);

    shape.setSize(sf::Vector2f(static_cast<float>(CHARACTER_ASSET_SIZE),
        static_cast<float>(CHARACTER_ASSET_SIZE)));

    shape.setTexture(&Shared::playerTexture);

    // préparation de la staminaBar pour le jetpack
    jetpackStaminaBarRect.setOutlineThickness(5.f);
    jetpackStaminaBarRect.setOutlineColor(sf::Color::White);
    jetpackStaminaBarRect.setSize(sf::Vector2f(100, 10));

    slideStaminaBarRect.setOutlineThickness(5.f);
    slideStaminaBarRect.setOutlineColor(sf::Color::White);
    slideStaminaBarRect.setSize(sf::Vector2f(slideStaminaMax, 10));

    shape.setPosition(sf::Vector2f(STGS::WIDTH * 0.05, STGS::HEIGHT - shape.getSize().y - STGS::HEIGHT / 10));

    // initialisation des sons


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

bool Player::collision(Map& map, int& pessos) {
    const std::vector<Obstacle*>& vectObs = map.getVectObs();
    const std::vector<Collectible*>& vectCollectible = map.getCollectible();
    const std::vector<Plateform*>& vectPlat = map.getPlateform();

    for (auto it = vectObs.begin(); it != vectObs.end(); ++it) {
        auto& obstacle = *it;
        if (getFeetBounds().findIntersection(obstacle->getSafePlaceBounds())) {
            shape.setPosition({ shape.getPosition().x, obstacle->getSafePlaceBounds().position.y - shape.getSize().y });
            velocity.y = 0;
            state = GROUNDED;
            stateMove = PLATEFORMING;
            return true;
        }
        else if (!isInvincible && shape.getGlobalBounds().findIntersection(obstacle->shape.getGlobalBounds()) && stateMove != SLIDING) {
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
            shape.setPosition({ shape.getPosition().x, plateform->shape.getGlobalBounds().position.y - shape.getSize().y });
            velocity.y = 0;
            state = GROUNDED;
            stateMove = PLATEFORMING;
            return true;
        }
    }
    if (getFeetBounds().findIntersection(map.getBounds()) && velocity.y > 0) {
        shape.setPosition({ shape.getPosition().x, map.getBounds().position.y - shape.getSize().y });
        velocity.y = 0;
        state = GROUNDED;
        stateMove = RUNNING;
        return true;
    }
    else if (getFeetBounds().findIntersection(map.getBounds2()) && velocity.y > 0) {
        shape.setPosition({ shape.getPosition().x, map.getBounds2().position.y - shape.getSize().y });
        velocity.y = 0;
        state = GROUNDED;
        stateMove = RUNNING;
        return true;
    }
    return false;
}

void Player::playerMovement(float deltaTime, Map& map, int& pessos) {
    if ((stateMove == RUNNING || stateMove == PLATEFORMING || stateMove == SLIDING) && jetpackStamina < 100)
        jetpackStamina++;

    if (slideStamina < slideStaminaMax && stateMove != SLIDING) {
        slideStamina++;
    }

    if (!collision(map, pessos)) 
        velocity.y += gravity * deltaTime;

    if (shape.getPosition().y < 0) {
        shape.setPosition({ shape.getPosition().x, 1 });
        velocity.y += gravity * deltaTime;
    }

    position.y = velocity.y * deltaTime;

    shape.move({ position });

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && slideStamina > 0 && !isReloadSlideBar) {
        stateMove = SLIDING;
        slideStamina--;
        if (state != GROUNDED) {
            velocity.y + 100000 * deltaTime;
            if (soundJohnCena.getStatus() != sf::SoundSource::Status::Playing && life != 0) soundJohnCena.play();
        }
    }
    if (slideStamina >= 10) {
        isReloadSlideBar = false;
    }
    else if (slideStamina <= 1) {
        isReloadSlideBar = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
        jump(deltaTime);
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
        soundManager(Shared::bufferRun);
        shape.setTexture(&Shared::playerTexture);
        animRun.y = 0; // reset le cycle d'anim sur y car on a pas d'anim sur l'axe y
        animJump.x = 0;

        if (clockRun.getElapsedTime().asMilliseconds() > 55) { // horloge qui permet de modifier la vitesse d'anim
            animRun.x++; // on met +1 a notre anim donc change de "case"
            clockRun.restart(); // on restart la clock pour continuer
        }
        if (animRun.x > 5) // si on atteint la "fin de l'image" (la fin des "cases")
            animRun.x = 0; // on reset l'image et on recommence
        shape.setTextureRect(sf::IntRect({ animRun.x * CHARACTER_ASSET_SIZE, animRun.y * CHARACTER_ASSET_SIZE }, { CHARACTER_ASSET_SIZE, CHARACTER_ASSET_SIZE })); // on set le rect pour prendre que le 120x80
        break;
    case JUMPING:
        soundManager(Shared::bufferJump);
        shape.setTexture(&Shared::playerJumpTexture);
        animJump.y = 0;

        if (clockJump.getElapsedTime().asMilliseconds() > 45) {
            animJump.x++;
            clockJump.restart();
        }
        if (animJump.x > 5)
            animJump.x = 5;
        shape.setTextureRect(sf::IntRect({ animJump.x * CHARACTER_ASSET_SIZE, animJump.y * CHARACTER_ASSET_SIZE }, { CHARACTER_ASSET_SIZE, CHARACTER_ASSET_SIZE }));
        break;
    case JETPACKING:
        soundManager(Shared::bufferJetpack);
        shape.setTexture(&Shared::playerJetpackTexture);
        animJetpack.y = 0;
        animJump.x = 0;

        if (clockJetpack.getElapsedTime().asMilliseconds() > 45) {
            animJetpack.x++;
            clockJetpack.restart();
        }
        if (animJetpack.x > 1)
            animJetpack.x = 0;
        shape.setTextureRect(sf::IntRect({ animJetpack.x * CHARACTER_ASSET_SIZE, animJetpack.y * CHARACTER_ASSET_SIZE }, { CHARACTER_ASSET_SIZE, CHARACTER_ASSET_SIZE }));
        break;
    case PLATEFORMING:
        soundManager(Shared::bufferRunGravel);
        shape.setTexture(&Shared::playerTexture);
        animRun.y = 0; // reset le cycle d'anim sur y car on a pas d'anim sur l'axe y
        animJump.x = 0;

        if (clockRun.getElapsedTime().asMilliseconds() > 55) { // horloge qui permet de modifier la vitesse d'anim
            animRun.x++; // on met +1 a notre anim donc change de "case"
            clockRun.restart(); // on restart la clock pour continuer
        }
        if (animRun.x > 5) // si on atteint la "fin de l'image" (la fin des "cases")
            animRun.x = 0; // on reset l'image et on recommence
        shape.setTextureRect(sf::IntRect({ animRun.x * CHARACTER_ASSET_SIZE, animRun.y * CHARACTER_ASSET_SIZE }, { CHARACTER_ASSET_SIZE, CHARACTER_ASSET_SIZE })); // on set le rect pour prendre que le 120x80
        break;
    case SLIDING:
        animJump.x = 0;
        if(state == GROUNDED) soundManager(Shared::bufferSlide);
        shape.setTexture(&Shared::playerSlideTexture);
        shape.setTextureRect(sf::IntRect({ 0, 0 }, { 128, 128 })); // on set le rect pour prendre que le 120x80
        break;
    }
}

void Player::staminaGestion() {

    if (jetpackStamina >= 60)
        jetpackStaminaBar.setFillColor(sf::Color::Green);
    else if (jetpackStamina < 30)
        jetpackStaminaBar.setFillColor(sf::Color::Red);
    else if (jetpackStamina < 60)
        jetpackStaminaBar.setFillColor(sf::Color::Yellow);

    jetpackStaminaBar.setSize(sf::Vector2f(jetpackStamina, 10));
    jetpackStaminaBar.setPosition(sf::Vector2f(shape.getPosition().x + 10, shape.getPosition().y - 30));
    jetpackStaminaBarRect.setPosition(sf::Vector2f(shape.getPosition().x + 10, shape.getPosition().y - 30));

    if (slideStamina != slideStaminaMax) {
        slideStaminaBar.setFillColor(sf::Color::Cyan);
    }
    else {
        slideStaminaBar.setFillColor(sf::Color::Magenta);
    }
    
    slideStaminaBar.setSize(sf::Vector2f(slideStamina, 10));
    slideStaminaBar.setPosition(sf::Vector2f(shape.getPosition().x + 10, shape.getPosition().y - 60));
    slideStaminaBarRect.setPosition(sf::Vector2f(shape.getPosition().x + 10, shape.getPosition().y - 60));
}

void Player::invincibility(Shop& shop) {
    

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
            if (shop.getSkin() == 1)
                shape.setFillColor(sf::Color::Green);
            else if (shop.getSkin() == 2)
                shape.setFillColor(sf::Color::Magenta);
            else if (shop.getSkin() == 3)
                shape.setFillColor(sf::Color::Yellow);
            else
                shape.setFillColor(sf::Color::White);
    }
    else
        if (shop.getSkin() == 1)
            shape.setFillColor(sf::Color::Green);
        else if (shop.getSkin() == 2)
            shape.setFillColor(sf::Color::Magenta);
        else if (shop.getSkin() == 3)
            shape.setFillColor(sf::Color::Yellow);
        else
            shape.setFillColor(sf::Color::White);
}

void Player::soundManager(sf::SoundBuffer& buffer) {
    const sf::SoundBuffer& currentBuffer = sound.getBuffer();

    if (&currentBuffer != &buffer && life != 0) {
        sound.stop();
        sound.setBuffer(buffer);

        if (&buffer == &Shared::bufferJump)
            sound.setLooping(false);
        else
            sound.setLooping(true);

        sound.setVolume(volumeSound);
        sound.play();
    }
    else if (sound.getStatus() != sf::SoundSource::Status::Playing && life != 0)
        sound.play();
}

void Player::stopSounds()
{
    sound.stop();
    soundCoin.stop();
    soundDeath.stop();
}

void Player::update(float deltaTime, Map& map, int& pessos, Shop& shop) {

    if (life != 0) {
        invincibility(shop);
        animationTakeDamage();
        playerMovement(deltaTime, map, pessos);
        animationManager(deltaTime);
        staminaGestion();
    }
    else {
        sound.stop();
        soundCoin.stop();
        soundDeath.stop();
    }
}

void Player::draw(sf::RenderWindow& window) {
    if (life != 0) {
        window.draw(jetpackStaminaBarRect);
        window.draw(jetpackStaminaBar);
        window.draw(slideStaminaBarRect);
        window.draw(slideStaminaBar);
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

sf::FloatRect Player::getSlideBounds() const {
    sf::FloatRect bounds = shape.getGlobalBounds();
    float slide = bounds.size.y * 0.0001f;
    sf::Vector2f slidePos(bounds.position.x, bounds.position.y + bounds.size.y - slide);
    sf::Vector2f slideSize(bounds.size.x, slide);
    return sf::FloatRect(slidePos, slideSize);
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

int Player::getVolume()
{
    return volumeSound;
}

void Player::setVolumeLess()
{
    volumeSound--;
}

void Player::setVolumeUp()
{
    volumeSound++;
}

void Player::setVolume(int sound)
{
    volumeSound = sound;
}

int Player::getLife() { return life; }
void Player::setLife(int l) { life = l; }

void Player::animationTakeDamage() {
    if (takeDamageClock.getElapsedTime().asSeconds() >= 2.f) {
        takeDamageClock.stop();
        takeDamageBool = false;
        return;
    }
    if (!takeDamageBool)
        return;
}
