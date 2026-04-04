#pragma once
#include "../masla.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <box2d/box2d.h>


enum PlatformEffect { None, Lengthen, Shorten };

struct Block {
    sf::RectangleShape shape;
    sf::RectangleShape line;
    b2Body* body = nullptr;
    bool markedForRemoval = false;
    uintptr_t id = 0; 
};

void PlatformSpawn();

void PlatformRemoval();

void PlatformErase();

void PlatformSpeed(float dt);

