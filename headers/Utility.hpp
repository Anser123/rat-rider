#pragma once
#include "../masla.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <box2d/box2d.h>
#include <fstream>

const float PIXELS_PER_METER = 50.0f;
const float METERS_PER_PIXEL = 1.0f / PIXELS_PER_METER;

b2Vec2 toMeters(const sf::Vector2f& pixels);

sf::Vector2f toPixels(const b2Vec2& meters);

float lerp(float a, float b, float t);

int loadHighScore(const std::string& filename);

void saveHighScore(const std::string& filename, int highscore);
