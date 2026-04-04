#pragma once

#include "../masla.hpp"
#include <vector>
#include <random>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <box2d/box2d.h>

#include "../headers/Utility.hpp"
#include "../headers/Contact.hpp"
#include "../headers/Textures.hpp"
#include "../headers/ControlRoom.hpp"
#include "../headers/Platform.hpp"
#include "../headers/Player.hpp"
#include "../headers/Collectible.hpp"

enum GameState { StartScreen, PlayingSingle, PlayingMulti, GameOver };

extern b2Vec2 gravity;
extern b2World world;
void worldInit();

extern std::vector<b2Body*> collectiblesToRemoveFromWorld;
extern PlayerContactListener contactListener;

extern b2BodyDef ceilingBodyDef;

void Player1Init();
extern sf::Sprite playerSprite;
extern b2Body* playerBody;
extern int jumpsRemaining;
extern bool fastFallActive;
extern bool player1Alive;

void Player2Init();
extern sf::Sprite player2Sprite;
extern b2Body* player2Body;
extern int jumpsRemaining2;
extern bool fastFallActive2;
extern bool player2Alive;

extern int winner;

extern std::vector<Block> blocks;
extern std::vector<Collectible> collectibles;
extern uintptr_t nextPlatformId;

extern GameState currentState;
extern sf::Clock spawnClock;
extern float nextSpawnTime;
extern sf::Clock deltaClock;
extern float gameTime;

extern sf::Clock playerAnimClock;
extern sf::Clock player2AnimClock;

extern int score;
extern int highScore;
extern PlatformEffect currentPlatformEffect;
extern sf::Clock platformEffectClock;
extern bool isRainingMagenta;
extern sf::Clock magentaRainClock;
extern sf::Clock magentaRainSpawnClock;

extern std::random_device rd;
extern std::mt19937 gen;
extern std::uniform_real_distribution<float> yPosDist;
extern std::uniform_real_distribution<float> initialSpawnTimeDist;
extern std::uniform_real_distribution<float> collectibleTypeDist;
extern std::uniform_real_distribution<float> rainXPosDist;



void SingleMode();

void MultiMode();

void SingleStartAndEnd();

void MultiStartAndEnd();

void ScoreUpdate();
