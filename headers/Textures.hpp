#pragma once
#include "../masla.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <box2d/box2d.h>

void LoadBackground(unsigned int windowWidth, unsigned int windowHeight);
void LoadTextures();
void LoadSounds();

extern sf::Texture story1Texture;
extern sf::Sprite story1Sprite;
extern sf::Texture story2Texture;
extern sf::Sprite story2Sprite;
extern sf::Texture story3Texture;
extern sf::Sprite story3Sprite;
extern sf::Texture backgroundTexture;
extern sf::Sprite backgroundSprite;
extern sf::Texture staticPlayerTexture;
extern sf::Texture staticPlayerTexture2;
extern sf::Texture jumpPlayerTexture;
extern sf::Texture staticPlayer2Texture;
extern sf::Texture staticPlayer2Texture2;
extern sf::Texture jumpPlayer2Texture;

extern sf::Texture collectibleTextures[6];

extern sf::Font font;


extern sf::SoundBuffer collectBuffer;
extern sf::SoundBuffer GreenOrbBuffer;
extern sf::SoundBuffer RedOrbBuffer;
extern sf::SoundBuffer PoisonBuffer;
extern sf::SoundBuffer CollectCheese;
extern sf::SoundBuffer JumpBuffer;
extern sf::SoundBuffer FallBuffer;
extern sf::SoundBuffer GameOverBuffer;
extern sf::SoundBuffer GameStartBuffer;

extern sf::Sound collectSound;
extern sf::Sound GreenOrbSound;
extern sf::Sound RedOrbSound;
extern sf::Sound PoisonSound;
extern sf::Sound CheeseSound;
extern sf::Sound JumpSound;
extern sf::Sound FallSound;
extern sf::Sound GameOverSound;
extern sf::Sound GameStartSound;

extern sf::Music backgroundMusic;

extern sf::Text gameOverText;
extern sf::Text scoreText;
extern sf::Text highScoreText;
extern sf::Text titleText;
extern sf::Text singlePlayerText;
extern sf::Text multiPlayerText;
