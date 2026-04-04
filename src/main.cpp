#include "../masla.hpp"
#include "../headers/Utility.hpp"
#include "../headers/Contact.hpp"
#include "../headers/Platform.hpp"
#include "../headers/Collectible.hpp"
#include "../headers/Game.hpp"
#include "../headers/ControlRoom.hpp"
#include "../headers/Textures.hpp"
#include "../headers/Player.hpp"

int main() {
    
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Rat Rider");
    window.setFramerateLimit(60);

    LoadBackground(windowWidth,windowHeight);
    LoadTextures();
    LoadSounds();

    worldInit();
    Player1Init();
    Player2Init();
 
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (currentState == GameState::StartScreen) {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Num1) {
                        window.clear();
                        window.draw(story1Sprite);
                        window.display();
                        sf::sleep(sf::seconds(4));
                        window.clear();
                        window.draw(story2Sprite);
                        window.display();
                        sf::sleep(sf::seconds(4));
                        SingleMode();
                    } else if (event.key.code == sf::Keyboard::Num2) {
                        window.clear();
                        window.draw(story1Sprite);
                        window.display();
                        sf::sleep(sf::seconds(4));
                        window.clear();
                        window.draw(story2Sprite);
                        window.display();
                        sf::sleep(sf::seconds(4));
                        window.clear();
                        window.draw(story3Sprite);
                        window.display();
                        sf::sleep(sf::seconds(4));
                        MultiMode();
                    }
                }
            } else if (currentState == GameState::PlayingSingle) {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W) {
                        if (playerBody && jumpsRemaining > 0) {
                            Player1Jump();
                        }
                    } else if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S) {
                        fastFallActive = true;
                    }
                }
                if (event.type == sf::Event::KeyReleased) {
                    if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S) {
                        fastFallActive = false;
                    }
                }
            } else if (currentState == GameState::PlayingMulti) {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Up) {
                        if (playerBody && jumpsRemaining > 0) {
                            Player1Jump();
                        }
                    } else if (event.key.code == sf::Keyboard::Down) {
                        fastFallActive = true;
                    }
                    if (event.key.code == sf::Keyboard::W) {
                        if (player2Body && jumpsRemaining2 > 0) {
                            Player2Jump();
                        }
                    } else if (event.key.code == sf::Keyboard::S) {
                        fastFallActive2 = true;
                    }
                }
                if (event.type == sf::Event::KeyReleased) {
                    if (event.key.code == sf::Keyboard::Down) {
                        fastFallActive = false;
                    }
                    if (event.key.code == sf::Keyboard::S) {
                        fastFallActive2 = false;
                    }
                }
            }
        }

        float dt = deltaClock.restart().asSeconds();
        if (currentState != GameState::PlayingSingle && currentState != GameState::PlayingMulti) {
            dt = 0;
        } else {
            dt = std::min(dt, 0.1f);
            gameTime += dt;

            Player1Fall();
            Player2Fall();

            world.Step(dt, 8, 3);
            
            PlayerPosUpdate();
            
            PlatformRemoval();

            if (currentState == GameState::PlayingSingle || currentState == GameState::PlayingMulti) {
                CollectibleRemoval();
            }
            
            if (currentState == GameState::PlayingSingle || currentState == GameState::PlayingMulti) {
                Scoring();
            } else { 
                NotCollectibleContact();
            }

            PlatformErase();

            CollectibleErase();
            
            if (currentState == GameState::PlayingSingle) {
                SingleStartAndEnd();
            } else if (currentState == GameState::PlayingMulti) {
                MultiStartAndEnd();
            } 
            
            if (currentState == GameState::PlayingSingle || currentState == GameState::PlayingMulti) {
                CheeseRain();
            }

            float currentMinLength = baseMinLength;
            float currentMaxLength = baseMaxLength;
            sf::Color currentBlockColor = defaultBlockColor;

            if (currentState == GameState::PlayingSingle || currentState == GameState::PlayingMulti) { 
                if (currentPlatformEffect == PlatformEffect::Lengthen) {
                    currentMinLength = baseMinLength * lengthenFactor;
                    currentMaxLength = baseMaxLength * lengthenFactor;
                    currentBlockColor = greenBlockColor;
                } else if (currentPlatformEffect == PlatformEffect::Shorten) {
                    currentMinLength = baseMinLength * shortenFactor;
                    currentMaxLength = baseMaxLength * shortenFactor;
                    currentBlockColor = redBlockColor;
                }
            }

            std::uniform_real_distribution<float> currentLengthDist(currentMinLength, currentMaxLength);

            if (spawnClock.getElapsedTime().asSeconds() >= nextSpawnTime) {
                Block newBlock;
                float blockLength = currentLengthDist(gen);
                float spawnY = yPosDist(gen);
                sf::Vector2f spawnPos(windowWidth + blockLength / 2.f, spawnY);

                newBlock.shape.setSize(sf::Vector2f(blockLength, fixedHeight));
                newBlock.shape.setFillColor(currentBlockColor);
                newBlock.shape.setOutlineColor(sf::Color::Black);
                newBlock.shape.setOutlineThickness(2.5f);
                newBlock.shape.setOrigin(blockLength / 2.f, fixedHeight / 2.f);
                newBlock.shape.setPosition(spawnPos);

                newBlock.line.setSize(sf::Vector2f(15.f, 500));
                newBlock.line.setFillColor(sf::Color(150,150,150));
                newBlock.line.setOutlineColor(sf::Color::Black);
                newBlock.line.setOutlineThickness(2.5f);
                newBlock.line.setOrigin(7.5f, 0.f);
                newBlock.line.setPosition(spawnPos.x, spawnPos.y + fixedHeight / 2.f);

                b2BodyDef blockBodyDef;
                blockBodyDef.type = b2_kinematicBody;
                blockBodyDef.position = toMeters(spawnPos);
                newBlock.body = world.CreateBody(&blockBodyDef);
                newBlock.id = nextPlatformId++;

                b2PolygonShape blockBox;
                blockBox.SetAsBox(toMeters(sf::Vector2f(blockLength / 2.f, fixedHeight / 2.f)).x, toMeters(sf::Vector2f(blockLength / 2.f, fixedHeight / 2.f)).y);

                b2FixtureDef blockFixtureDef;
                blockFixtureDef.shape = &blockBox;
                blockFixtureDef.friction = 0.7f;
                blockFixtureDef.userData.pointer = newBlock.id;
                newBlock.body->CreateFixture(&blockFixtureDef);

                newBlock.body->SetLinearVelocity(b2Vec2(toMeters(sf::Vector2f(-blockSpeed, 0.f)).x, 0.0f));

                bool visualOverlap = false;
                sf::FloatRect candidateBounds = newBlock.shape.getGlobalBounds();
                candidateBounds.left -= 50; 
                candidateBounds.width += 100;

                for (const auto& block : blocks) {
                    if (!block.markedForRemoval && block.body && candidateBounds.intersects(block.shape.getGlobalBounds())) {
                        visualOverlap = true;
                        break;
                    }
                }

                if (!visualOverlap) {
                    blocks.push_back(newBlock);
                }    

                if (!visualOverlap) {
                    if (currentState == GameState::PlayingSingle) {
                        SingleModeCollectibleSpawn(spawnPos, newBlock);
                    } 

                if (currentState == GameState::PlayingMulti) {
                    MultiModeCollectibleSpawn(spawnPos, newBlock);
                } 
            } else {
                world.DestroyBody(newBlock.body);
            }
                spawnClock.restart();
                std::uniform_real_distribution<float> nextSpawnTimeDist(minSpawnTime, maxSpawnTime);
                nextSpawnTime = nextSpawnTimeDist(gen);
            } 

            PlatformSpeed(dt);
            
            if (currentState == GameState::PlayingSingle) {
                ScoreUpdate();
            }
        } 
        
        window.clear(sf::Color(50, 50, 100));
        window.draw(backgroundSprite);

        if (currentState == GameState::StartScreen) {
            window.draw(titleText);
            window.draw(singlePlayerText);
            window.draw(multiPlayerText);
        } else { 
            for (const auto& block : blocks) {
                window.draw(block.line);
                window.draw(block.shape);
            }

            if (currentState == GameState::PlayingSingle || currentState == GameState::PlayingMulti) {
                for (const auto& collectible : collectibles) {
                    window.draw(collectible.sprite);
                }
            }

            if (playerBody) window.draw(playerSprite);
            if (player2Body) window.draw(player2Sprite); 
            
            if (currentState == GameState::PlayingSingle) {
                window.draw(scoreText);
                window.draw(highScoreText);
            } else if (currentState == GameState::GameOver) {
                window.draw(gameOverText);
            }
        }

        window.display();
    } 

    if (playerBody) world.DestroyBody(playerBody);
    if (player2Body) world.DestroyBody(player2Body);
    
    return 0;
}
