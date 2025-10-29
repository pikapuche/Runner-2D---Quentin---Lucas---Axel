#include "AssetManager.hpp"

#include <iostream>

AssetManager::AssetManager() {
	loadAssetsFromFiles();
}

void AssetManager::loadAssetsFromFiles() {
    if (!Shared::tileSetTexture.loadFromFile("Assets/tiles_map/RunnerTileSet.png"))
        std::cerr << "Erreur : impossible de charger RunnerTileSet.png\n";

    if (!Shared::collectibleTexture.loadFromFile("Assets/Images/Gold.png"))
        std::cerr << "Erreur : impossible de charger Gold.png\n";
    
    // MENU //
    
    if (!Shared::backgroundMenu.loadFromFile("Assets/tiles_map/spaceTitleBackground.png"))
        std::cerr << "Erreur : impossible de charger spaceTitleBackground.png\n";

    // MAP // 

    if (!Shared::backboardFirstTextureDifficultyOne.loadFromFile("Assets/tiles_map/backgroundFar.png"))
        std::cerr << "Erreur : backgroundFar.png\n";
    if (!Shared::backboardSecondTextureDifficultyOne.loadFromFile("Assets/tiles_map/backgroundNear.png"))
        std::cerr << "Erreur : backgroundNear.png\n";

    if (!Shared::backboardFirstTextureDifficultyTwo.loadFromFile("Assets/tiles_map/backgroundFar_2.png"))
        std::cerr << "Erreur : backgroundFar_2.png\n";
    if (!Shared::backboardSecondTextureDifficultyTwo.loadFromFile("Assets/tiles_map/backgroundNear_2.png"))
        std::cerr << "Erreur : backgroundNear_2.png\n";

    if (!Shared::backboardFirstTextureDifficultyThree.loadFromFile("Assets/tiles_map/backgroundFar_3.png"))
        std::cerr << "Erreur : backgroundFar_3.png\n";
    if (!Shared::backboardSecondTextureDifficultyThree.loadFromFile("Assets/tiles_map/backgroundNear_3.png"))
        std::cerr << "Erreur : backgroundNear_3.png\n";

    if (!Shared::backboardFirstTextureDifficultyFour.loadFromFile("Assets/tiles_map/backgroundFar_4.png"))
        std::cerr << "Erreur : backgroundFar_4.png\n";
    if (!Shared::backboardSecondTextureDifficultyFour.loadFromFile("Assets/tiles_map/backgroundNear_4.png"))
        std::cerr << "Erreur : backgroundNear_4.png\n";

    if (!Shared::goldTexture.loadFromFile("Assets/Images/Gold.png"))
        std::cerr << "Erreur : Gold.png\n";

    if (!Shared::heart1Texture.loadFromFile("Assets/Images/Heart_Live.png"))
        std::cerr << "Erreur : Heart_Live.png\n";
    if (!Shared::heart2Texture.loadFromFile("Assets/Images/hello_kitty_heart.png"))
        std::cerr << "Erreur : hello_kitty_heart.png\n";
    if (!Shared::heart3Texture.loadFromFile("Assets/Images/coeur_brise_de_mon_amour infini.png"))
        std::cerr << "Erreur : coeur_brise_de_mon_amour infini.png\n";

    if (!Shared::groundTexture.loadFromFile("Assets/tiles_map/RunnerTileSet.png"))
        std::cerr << "Erreur : RunnerTileSet.png (groundTexture)\n";

    if (!Shared::trophyTexture.loadFromFile("Assets/Images/trophy.png"))
        std::cerr << "Erreur : trophy.png\n";

    if (!Shared::cadre1.loadFromFile("Assets/Images/cadre_1.png"))
        std::cerr << "Erreur : cadre_1.png\n";

    ///////////// PLAYER TEXTURE /////////////

    if (!Shared::playerTexture.loadFromFile("Assets/Character/Astronaut_RunV2.png"))
        std::cerr << "Erreur : Astronaut_RunV2.png\n";
    if (!Shared::playerJumpTexture.loadFromFile("Assets/Character/Astronaut_JumpV2.png"))
        std::cerr << "Erreur : Astronaut_JumpV2.png\n";
    if (!Shared::playerJetpackTexture.loadFromFile("Assets/Character/Astronaut_JetPack.png"))
        std::cerr << "Erreur : Astronaut_JetPack.png\n";
    if (!Shared::playerSlideTexture.loadFromFile("Assets/Character/Astronaut_Slide.png"))
        std::cerr << "Erreur : Astronaut_JetPack.png\n";

    ///////////// PLAYER SOUND /////////////

    if (!Shared::bufferRun.loadFromFile("Assets/SoundEffects/run.wav")) 
        std::cerr << "Erreur : run.wav\n";
    if (!Shared::bufferJump.loadFromFile("Assets/SoundEffects/jump.wav")) 
        std::cerr << "Erreur : jump.wav\n";
    if (!Shared::bufferJetpack.loadFromFile("Assets/SoundEffects/jetpack.wav")) 
        std::cerr << "Erreur : jetpack.wav\n";
    if (!Shared::bufferRunGravel.loadFromFile("Assets/SoundEffects/runGravel2.wav"))
        std::cerr << "Erreur : runGravel2.wav.wav\n";
    if (!Shared::bufferCoin.loadFromFile("Assets/SoundEffects/coin.wav")) 
        std::cerr << "Erreur : coin.wav\n";
    if (!Shared::bufferHurt.loadFromFile("Assets/SoundEffects/oof.wav"))
        std::cerr << "Erreur : oof.wav\n";
    if (!Shared::bufferSlide.loadFromFile("Assets/SoundEffects/slide.wav"))
        std::cerr << "Erreur : slide.wav\n";
}
