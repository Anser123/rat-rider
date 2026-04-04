#pragma once
#include "../masla.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <box2d/box2d.h>

extern const unsigned int windowWidth;
extern const unsigned int windowHeight;
extern const float fixedHeight;
extern const float baseMinLength;
extern const float baseMaxLength;
extern float minLength;
extern float maxLength;
extern float blockSpeed;
extern const float blockSpeedIncreaseFactor;
extern const float maxBlockSpeed;
extern float minSpawnTime;
extern float maxSpawnTime;
extern const float minSpawnTimeBase;
extern const float maxSpawnTimeBase;
extern const float playerWidth;
extern const float playerHeight;
extern const float playerJumpForce;
extern const int maxJumps;
extern float collectibleRadius;
extern const float collectibleSpawnChance ;
extern const float magentaCollectibleProb ;
extern const float orangeCollectibleProb ;
extern const float greenCollectibleProb ;
extern const float redCollectibleProb ;
extern const float whiteCollectibleProb ;
extern const float collectibleSpawnChanceMulti ;
extern const float greenCollectibleProbMulti ;
extern const float redCollectibleProbMulti ;
extern const float minusScoreCollectibleProb ;
extern const float platformEffectDuration ;
extern const float lengthenFactor;
extern const float shortenFactor;
extern const float magentaRainDuration;
extern const float magentaRainSpawnInterval;
extern const float magentaRainSpeed;
extern const float fastFallGravityScale;

extern sf::Color defaultBlockColor;
extern sf::Color greenBlockColor;
extern sf::Color redBlockColor;



