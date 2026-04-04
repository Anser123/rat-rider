#pragma once
#include "../masla.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <box2d/box2d.h>

#include "../headers/Platform.hpp"


enum CollectibleType { Magenta, Orange, Green, Red, White, MinusScore };

struct Collectible {
    sf::Sprite sprite;
    CollectibleType type;
    b2Body* body = nullptr;
    bool markedForRemoval = false;
};

void CollectibleRemoval();

void NotCollectibleContact();

void Scoring();

void CollectibleErase();

void CheeseRain();

void SingleModeCollectibleSpawn(sf::Vector2f spawnPos, Block newBlock);

void MultiModeCollectibleSpawn(sf::Vector2f spawnPos, Block newBlock);
