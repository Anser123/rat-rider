#include "../headers/Utility.hpp"

b2Vec2 toMeters(const sf::Vector2f& pixels) {
    return b2Vec2(pixels.x * METERS_PER_PIXEL, pixels.y * METERS_PER_PIXEL);
}

sf::Vector2f toPixels(const b2Vec2& meters) {
    return sf::Vector2f(meters.x * PIXELS_PER_METER, meters.y * PIXELS_PER_METER);
}

float lerp(float a, float b, float t) {
    return a + t * (b - a);
}

int loadHighScore(const std::string& filename) {
    std::ifstream file(filename);
    int highscore = 0;
    if (file.is_open()) {
        file >> highscore;
        file.close();
    }
    return highscore;
}

void saveHighScore(const std::string& filename, int highscore) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << highscore;
        file.close();
    }
}