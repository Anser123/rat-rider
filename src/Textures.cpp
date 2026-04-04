#include "../headers/Textures.hpp"


sf::Texture story1Texture;
sf::Sprite story1Sprite;
sf::Texture story2Texture;
sf::Sprite story2Sprite;
sf::Texture story3Texture;
sf::Sprite story3Sprite;
sf::Texture backgroundTexture;
sf::Sprite backgroundSprite;
sf::Texture staticPlayerTexture;
sf::Texture staticPlayerTexture2;
sf::Texture jumpPlayerTexture;
sf::Texture staticPlayer2Texture;
sf::Texture staticPlayer2Texture2;
sf::Texture jumpPlayer2Texture;
sf::Texture collectibleTextures[6];
sf::Font font;
sf::SoundBuffer collectBuffer;
sf::SoundBuffer GreenOrbBuffer;
sf::SoundBuffer RedOrbBuffer;
sf::SoundBuffer PoisonBuffer;
sf::SoundBuffer CollectCheese;
sf::SoundBuffer JumpBuffer;
sf::SoundBuffer FallBuffer;
sf::SoundBuffer GameOverBuffer;
sf::SoundBuffer GameStartBuffer;
sf::Sound collectSound;
sf::Sound GreenOrbSound;
sf::Sound RedOrbSound;
sf::Sound PoisonSound;
sf::Sound CheeseSound;
sf::Sound JumpSound;
sf::Sound FallSound;
sf::Sound GameOverSound;
sf::Sound GameStartSound;
sf::Music backgroundMusic;

sf::Text gameOverText("Game Over!", font, 50);
sf::Text scoreText("Score 0", font, 30);
sf::Text highScoreText("High Score 0", font, 30);
sf::Text titleText("Rat Rider", font, 80);
sf::Text singlePlayerText("1. Single Player", font, 40);
sf::Text multiPlayerText("2. Multiplayer", font, 40);


void LoadBackground(unsigned int windowWidth, unsigned int windowHeight) {

    story1Texture.loadFromFile("./resources/textures/story1.png");
    story1Sprite.setTexture(story1Texture);
    story1Sprite.setScale(
        static_cast<float>(windowWidth) / story1Texture.getSize().x,
        static_cast<float>(windowHeight) / story1Texture.getSize().y
    
    );

    story2Texture.loadFromFile("./resources/textures/story2.png");
    story2Sprite.setTexture(story2Texture);
    story2Sprite.setScale(
        static_cast<float>(windowWidth) / story2Texture.getSize().x,
        static_cast<float>(windowHeight) / story2Texture.getSize().y
    
    );

    story3Texture.loadFromFile("./resources/textures/story3.png");
    story3Sprite.setTexture(story3Texture);
    story3Sprite.setScale(
        static_cast<float>(windowWidth) / story3Texture.getSize().x,
        static_cast<float>(windowHeight) / story3Texture.getSize().y
    
    );

    backgroundTexture.loadFromFile("./resources/textures/silhouette.jpg");
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        static_cast<float>(windowWidth) / backgroundTexture.getSize().x,
        static_cast<float>(windowHeight) / backgroundTexture.getSize().y
    );
    
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setStyle(sf::Text::Bold);
    
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(25.f, 10.f);

    highScoreText.setFillColor(sf::Color::White);
    highScoreText.setPosition(930.f, 10.f);

    titleText.setFillColor(sf::Color::Yellow);
    titleText.setStyle(sf::Text::Bold);
    titleText.setPosition(windowWidth / 4.f + 40.f , windowHeight / 4.f);

    singlePlayerText.setFillColor(sf::Color::White);
    singlePlayerText.setPosition(windowWidth / 4.f + 80.f , windowHeight / 2.f - 50.f);

    multiPlayerText.setFillColor(sf::Color::White);
    multiPlayerText.setPosition(windowWidth / 4.f + 80.f , windowHeight / 2.f + 20.f);

}

void LoadTextures()
{
    staticPlayerTexture.loadFromFile("./resources/textures/Player1_Idle_1.png");
    staticPlayerTexture2.loadFromFile("./resources/textures/Player1_Idle_2.png");
    jumpPlayerTexture.loadFromFile("./resources/textures/Player1_Jump.png");
    staticPlayer2Texture.loadFromFile("./resources/textures/Player2_Idle_1.png");
    staticPlayer2Texture2.loadFromFile("./resources/textures/Player2_Idle_2.png");
    jumpPlayer2Texture.loadFromFile("./resources/textures/Player2_Jump.png");

    collectibleTextures[0].loadFromFile("./resources/textures/Cheese.png");
    collectibleTextures[1].loadFromFile("./resources/textures/Pizza.png");
    collectibleTextures[2].loadFromFile("./resources/textures/Long_Platform_Green.png");
    collectibleTextures[3].loadFromFile("./resources/textures/Short_Platform_Red.png");
    collectibleTextures[4].loadFromFile("./resources/textures/Cheese_Rain.png");
    collectibleTextures[5].loadFromFile("./resources/textures/PoisonBottle.png");

    font.loadFromFile("./resources/fonts/Retro.ttf");

    
}

void LoadSounds()
{
    collectBuffer.loadFromFile("./resources/sounds/collectible.wav");
    collectSound.setVolume(30);
    collectSound.setBuffer(collectBuffer);

    GreenOrbBuffer.loadFromFile("./resources/sounds/GreenOrb.mp3");
    GreenOrbSound.setVolume(40);
    GreenOrbSound.setBuffer(GreenOrbBuffer);

    RedOrbBuffer.loadFromFile("./resources/sounds/RedOrb.mp3");
    RedOrbSound.setVolume(60);
    RedOrbSound.setBuffer(RedOrbBuffer);

    PoisonBuffer.loadFromFile("./resources/sounds/Poison.mp3");
    PoisonSound.setVolume(60);
    PoisonSound.setBuffer(PoisonBuffer);

    CollectCheese.loadFromFile("./resources/sounds/CollectCheese.mp3");
    CheeseSound.setVolume(40);
    CheeseSound.setBuffer(CollectCheese);

    JumpBuffer.loadFromFile("./resources/sounds/Jump.mp3");
    JumpSound.setVolume(35);
    JumpSound.setBuffer(JumpBuffer);

    FallBuffer.loadFromFile("./resources/sounds/Fall.mp3");
    FallSound.setVolume(35);
    FallSound.setBuffer(FallBuffer);

    GameOverBuffer.loadFromFile("./resources/sounds/GameOver.mp3");
    GameOverSound.setVolume(50);
    GameOverSound.setBuffer(GameOverBuffer);

    GameStartBuffer.loadFromFile("./resources/sounds/GameStart.mp3");
    GameStartSound.setVolume(100);
    GameStartSound.setBuffer(GameStartBuffer);
    
    backgroundMusic.openFromFile("./resources/sounds/background.ogg");
    backgroundMusic.setLoop(true);
    backgroundMusic.setVolume(25);

}
