#include "../headers/ControlRoom.hpp"

const unsigned int windowWidth = 1200;
const unsigned int windowHeight = 700;
const float fixedHeight = 20.f;
const float baseMinLength = 200.f;
const float baseMaxLength = 300.f;
float minLength = baseMinLength;
float maxLength = baseMaxLength;
float blockSpeed = 200.f;
const float blockSpeedIncreaseFactor = 7.5f;
const float maxBlockSpeed = 600.f;
float minSpawnTime = 2.5f;
float maxSpawnTime = 3.5f;
const float minSpawnTimeBase = 0.8f;
const float maxSpawnTimeBase = 1.5f;
const float playerWidth = 90.f;
const float playerHeight = 90.f;
const float playerJumpForce = 500.0f;
const int maxJumps = 1;
float collectibleRadius = 25.f;
const float collectibleSpawnChance = 0.85f;
const float magentaCollectibleProb = 0.35f;
const float orangeCollectibleProb = 0.20f;
const float greenCollectibleProb = 0.125f;
const float redCollectibleProb = 0.125f;
const float whiteCollectibleProb = 0.05f;
const float minusScoreCollectibleProb = 0.15f;
const float collectibleSpawnChanceMulti = 0.35f;
const float greenCollectibleProbMulti = 0.50f;
const float redCollectibleProbMulti = 0.50f;
const float platformEffectDuration = 10.0f;
const float lengthenFactor = 2.5f;
const float shortenFactor = 0.5f;
const float magentaRainDuration = 10.0f;
const float magentaRainSpawnInterval = 0.15f;
const float magentaRainSpeed = 400.0f;
const float fastFallGravityScale = 100.0f;

sf::Color defaultBlockColor = sf::Color(255, 200, 0);
sf::Color greenBlockColor = sf::Color::Green;
sf::Color redBlockColor = sf::Color::Red;


