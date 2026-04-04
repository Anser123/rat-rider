#include "../headers/Game.hpp"

b2Vec2 gravity(0.0f, 7.0f);
b2World world(gravity);

std::vector<b2Body*> collectiblesToRemoveFromWorld;
PlayerContactListener contactListener(collectiblesToRemoveFromWorld);
b2BodyDef ceilingBodyDef;

sf::Sprite playerSprite;
b2Body* playerBody = nullptr;
int jumpsRemaining = maxJumps;
bool fastFallActive = false;
bool player1Alive = true;

sf::Sprite player2Sprite;
b2Body* player2Body = nullptr;
int jumpsRemaining2 = maxJumps;
bool fastFallActive2 = false;
bool player2Alive = true;

int winner = 0;

std::vector<Block> blocks;
std::vector<Collectible> collectibles;
uintptr_t nextPlatformId = PLATFORM_ID_BASE;

GameState currentState = GameState::StartScreen;
sf::Clock spawnClock;
float nextSpawnTime = 0.f;
sf::Clock deltaClock;
float gameTime = 0.f;

sf::Clock playerAnimClock;
sf::Clock player2AnimClock;

int score = 0;
int highScore = loadHighScore("highscore.txt");
PlatformEffect currentPlatformEffect = PlatformEffect::None;
sf::Clock platformEffectClock;
bool isRainingMagenta = false;
sf::Clock magentaRainClock;
sf::Clock magentaRainSpawnClock;

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<float> yPosDist(windowHeight - 450.f, windowHeight - 150.f);
std::uniform_real_distribution<float> initialSpawnTimeDist(0.5f, 1.5f);
std::uniform_real_distribution<float> collectibleTypeDist(0.0f, 1.0f);
std::uniform_real_distribution<float> rainXPosDist(collectibleRadius, windowWidth - collectibleRadius);



void worldInit()
{
    world.SetContactListener(&contactListener);
    ceilingBodyDef.position.Set(toMeters(sf::Vector2f(windowWidth / 2.f, -10.f)).x, toMeters(sf::Vector2f(windowWidth / 2.f, -10.f)).y);
    b2Body* ceilingBody = world.CreateBody(&ceilingBodyDef);
    b2PolygonShape ceilingBox;
    ceilingBox.SetAsBox(toMeters(sf::Vector2f(windowWidth / 2.f, 10.f)).x, toMeters(sf::Vector2f(windowWidth / 2.f, 10.f)).y);
    b2Fixture* ceilingFixture = ceilingBody->CreateFixture(&ceilingBox, 0.0f);
    ceilingFixture->GetUserData().pointer = CEILING_ID;

}

void Player1Init()
{
    playerSprite.setTexture(staticPlayerTexture); 
    playerSprite.setScale(playerWidth / staticPlayerTexture.getSize().x, playerHeight / staticPlayerTexture.getSize().y);
    playerSprite.setOrigin(staticPlayerTexture.getSize().x / 2.f, staticPlayerTexture.getSize().y / 2.f); 

}

void Player2Init()
{
    player2Sprite.setTexture(staticPlayer2Texture); 
    player2Sprite.setScale(playerWidth / staticPlayer2Texture.getSize().x, playerHeight / staticPlayer2Texture.getSize().y);
    player2Sprite.setOrigin(staticPlayer2Texture.getSize().x / 2.f, staticPlayer2Texture.getSize().y / 2.f); 

}

void SingleMode()
{
    GameStartSound.play();
    currentState = GameState::PlayingSingle;
    score = 0;
    highScore = loadHighScore("highscore.txt");
    blocks.clear();
    collectibles.clear();
    collectiblesToRemoveFromWorld.clear();
    contactListener.reset();
    gameTime = 0.f;
    blockSpeed = 200.f;
    minLength = baseMinLength;
    maxLength = baseMaxLength;
    minSpawnTime = 2.5f;
    maxSpawnTime = 3.5f;
    currentPlatformEffect = PlatformEffect::None;
    isRainingMagenta = false;
    spawnClock.restart();
    deltaClock.restart();
    backgroundMusic.play();

    Player1Spawn();

    PlatformSpawn();

}

void MultiMode()
{
    GameStartSound.play();
    currentState = GameState::PlayingMulti;
    blocks.clear();
    collectibles.clear();
    collectiblesToRemoveFromWorld.clear();
    contactListener.reset();
    gameTime = 0.f;
    blockSpeed = 200.f;
    minLength = baseMinLength;
    maxLength = baseMaxLength;
    minSpawnTime = 2.5f;
    maxSpawnTime = 3.5f;
    currentPlatformEffect = PlatformEffect::None;
    isRainingMagenta = false;
    spawnClock.restart();
    deltaClock.restart();
    backgroundMusic.play();
    winner = 0;

    Player1Spawn();

    Player2Spawn();

    PlatformSpawn();
}

void SingleStartAndEnd()
{
    if (playerBody) { 
        if (contactListener.isGrounded(PLAYER1_ID)) {
            jumpsRemaining = maxJumps;
            playerSprite.setTexture(staticPlayerTexture);
        } else {
            playerSprite.setTexture(jumpPlayerTexture);
        }

        if (fastFallActive && !contactListener.isGrounded(PLAYER1_ID)) {
            FallSound.play();
            playerBody->SetGravityScale(fastFallGravityScale);
        } else {
            playerBody->SetGravityScale(1.0f); 
        }
         
        if ((playerBody && (playerBody->GetPosition().y > toMeters(sf::Vector2f(0, windowHeight + playerHeight)).y || playerBody->GetPosition().x < toMeters(sf::Vector2f(-playerWidth, 0)).x))) {
            GameOverSound.play();
            currentState = GameState::GameOver;
            backgroundMusic.stop();
            if (score > highScore) {
                highScore = score;
                saveHighScore("highscore.txt", highScore);
            }
            
            gameOverText.setString("Game Over!");
            sf::FloatRect textRect = gameOverText.getLocalBounds();
            gameOverText.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
            gameOverText.setPosition(sf::Vector2f(windowWidth/2.0f, windowHeight/2.0f - 100.f));
            
            if(playerBody) world.DestroyBody(playerBody);
            playerBody = nullptr;
        }
    } 
}

void MultiStartAndEnd()
{
                    
    if (player1Alive && playerBody) { 
        if (contactListener.isGrounded(PLAYER1_ID)) {
            jumpsRemaining = maxJumps;
            playerSprite.setTexture(staticPlayerTexture);
        } else {
            playerSprite.setTexture(jumpPlayerTexture);
        }

        if (fastFallActive && !contactListener.isGrounded(PLAYER1_ID)) {
            FallSound.play();
            playerBody->SetGravityScale(fastFallGravityScale);
        } else {
            playerBody->SetGravityScale(1.0f); 
        }
        
        if ((playerBody && (playerBody->GetPosition().y > toMeters(sf::Vector2f(0, windowHeight + playerHeight)).y || playerBody->GetPosition().x < toMeters(sf::Vector2f(-playerWidth, 0)).x))) {
            player1Alive = false;
            world.DestroyBody(playerBody);
            playerBody = nullptr; 
            if (player2Alive) winner = 2; 
            else winner = 0; 
        }
    }
    
    if (player2Alive && player2Body) { 
         if (contactListener.isGrounded(PLAYER2_ID)) {
            jumpsRemaining2 = maxJumps;
            player2Sprite.setTexture(staticPlayer2Texture);
        } else {
            player2Sprite.setTexture(jumpPlayer2Texture);
        }

        if (fastFallActive2 && !contactListener.isGrounded(PLAYER2_ID)) {
            FallSound.play();
            player2Body->SetGravityScale(fastFallGravityScale);
        } else {
            player2Body->SetGravityScale(1.0f); 
        }
        
        if ((player2Body && (player2Body->GetPosition().y > toMeters(sf::Vector2f(0, windowHeight + playerHeight)).y || player2Body->GetPosition().x < toMeters(sf::Vector2f(-playerWidth, 0)).x))) {
            player2Alive = false;
            world.DestroyBody(player2Body);
            player2Body = nullptr; 
            if (player1Alive) winner = 1; 
            else winner = 0; 
        }
    }
    
    if (!player1Alive || !player2Alive) {
        GameOverSound.play();
        currentState = GameState::GameOver;
        backgroundMusic.stop();
        
        std::string winMessage;
        if (winner == 1) winMessage = "Player 1 Wins!";
        else if (winner == 2) winMessage = "Player 2 Wins!";
        else winMessage = "Tie!"; 
        gameOverText.setString(winMessage);
        sf::FloatRect textRect = gameOverText.getLocalBounds();
        gameOverText.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
        gameOverText.setPosition(sf::Vector2f(windowWidth/2.0f, windowHeight/3.0f));
    }


}

void ScoreUpdate()
{
    scoreText.setString("Score \n  " + std::to_string(score));
    highScoreText.setString("High Score \n    " + std::to_string(highScore));
}