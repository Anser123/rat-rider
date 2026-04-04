#include "../headers/Collectible.hpp"
#include "../headers/Game.hpp"
#include "../headers/Platform.hpp"

void CollectibleRemoval()
{
    for (auto& collectible : collectibles) {
        if (collectible.body) {
            collectible.sprite.setPosition(toPixels(collectible.body->GetPosition()));
            if (collectible.sprite.getPosition().x < -collectible.sprite.getGlobalBounds().width / 2.f || collectible.sprite.getPosition().y > windowHeight + collectible.sprite.getGlobalBounds().height / 2.f) {
                collectible.markedForRemoval = true;
            }
        }
    }
}

void NotCollectibleContact()
{
    for (b2Body* bodyToRemove : collectiblesToRemoveFromWorld) {
        for (auto it = collectibles.begin(); it != collectibles.end(); ++it) {
            if (it->body == bodyToRemove) {
                it->markedForRemoval = true;
                break;
            }
        }
    }
    collectiblesToRemoveFromWorld.clear();
}

void Scoring()
{
    for (b2Body* bodyToRemove : collectiblesToRemoveFromWorld) {
        for (auto it = collectibles.begin(); it != collectibles.end(); ++it) {
            if (it->body == bodyToRemove) {
                switch (it->type) {
                    case CollectibleType::Magenta: score++; CheeseSound.play(); break;
                    case CollectibleType::Orange: score += 3; CheeseSound.play(); break;
                    case CollectibleType::Green: currentPlatformEffect = PlatformEffect::Lengthen; platformEffectClock.restart(); GreenOrbSound.play(); break;
                    case CollectibleType::Red: currentPlatformEffect = PlatformEffect::Shorten; platformEffectClock.restart(); RedOrbSound.play(); break;
                    case CollectibleType::White: isRainingMagenta = true; magentaRainClock.restart(); magentaRainSpawnClock.restart(); GreenOrbSound.play(); break;
                    case CollectibleType::MinusScore: score = std::max(0, score - 2); PoisonSound.play(); break;
                }
                it->markedForRemoval = true;
                break;
            }
        }
    }
    collectiblesToRemoveFromWorld.clear();
}

void CollectibleErase()
{
    collectibles.erase(std::remove_if(collectibles.begin(), collectibles.end(), [&](Collectible& collectible) {
        if (collectible.markedForRemoval && collectible.body) {
            world.DestroyBody(collectible.body);
            collectible.body = nullptr;
            return true;
        }
        return false;
    }), collectibles.end());


}

void CheeseRain()
{
    if (currentPlatformEffect != PlatformEffect::None) {
        if (platformEffectClock.getElapsedTime().asSeconds() >= platformEffectDuration) {
            currentPlatformEffect = PlatformEffect::None;
        }
    }
    if (isRainingMagenta) {
        if (magentaRainClock.getElapsedTime().asSeconds() >= magentaRainDuration) {
            isRainingMagenta = false;
        } else {
            if (magentaRainSpawnClock.getElapsedTime().asSeconds() >= magentaRainSpawnInterval) {
                Collectible rainCollectible;
                sf::Vector2f spawnPos(rainXPosDist(gen), -collectibleRadius);
                rainCollectible.type = CollectibleType::Magenta;
                uintptr_t collectibleUserData = MAGENTA_COLLECTIBLE_ID;
                sf::Texture* texturePtr = &collectibleTextures[0];
                rainCollectible.sprite.setTexture(*texturePtr);
                rainCollectible.sprite.setScale(
                    (collectibleRadius * 2.f) / rainCollectible.sprite.getTexture()->getSize().x,
                    (collectibleRadius * 2.f) / rainCollectible.sprite.getTexture()->getSize().y
                );
                rainCollectible.sprite.setOrigin(rainCollectible.sprite.getTexture()->getSize().x / 2.f, rainCollectible.sprite.getTexture()->getSize().y / 2.f);
                rainCollectible.sprite.setPosition(spawnPos);
                b2BodyDef collectibleBodyDef;
                collectibleBodyDef.type = b2_kinematicBody;
                collectibleBodyDef.position = toMeters(spawnPos);
                rainCollectible.body = world.CreateBody(&collectibleBodyDef);
                b2CircleShape collectibleCircle;
                collectibleCircle.m_radius = toMeters(sf::Vector2f(collectibleRadius, 0)).x;
                b2FixtureDef collectibleFixtureDef;
                collectibleFixtureDef.shape = &collectibleCircle;
                collectibleFixtureDef.isSensor = true;
                collectibleFixtureDef.userData.pointer = collectibleUserData;
                rainCollectible.body->CreateFixture(&collectibleFixtureDef);
                rainCollectible.body->SetLinearVelocity(b2Vec2(0.0f, toMeters(sf::Vector2f(0, magentaRainSpeed)).y));
                collectibles.push_back(rainCollectible);
                magentaRainSpawnClock.restart();
            }
        }
    }
}

void SingleModeCollectibleSpawn(sf::Vector2f spawnPos, Block newBlock)
{
    float collectibleRoll = collectibleTypeDist(gen);
                        if (collectibleRoll < collectibleSpawnChance) {
                            Collectible newCollectible;
                            sf::Vector2f collectiblePos = spawnPos;
                            collectiblePos.y -= (fixedHeight / 2.f + collectibleRadius + 5.f); 

                            float typeRoll = collectibleTypeDist(gen);
                            uintptr_t collectibleUserData = 0;
                            sf::Texture* texturePtr = nullptr;
                            CollectibleType type;

                            if (typeRoll < magentaCollectibleProb) {
                                type = CollectibleType::Magenta;
                                collectibleUserData = MAGENTA_COLLECTIBLE_ID;
                                texturePtr = &collectibleTextures[0];
                            } else if (typeRoll < magentaCollectibleProb + orangeCollectibleProb) {
                                type = CollectibleType::Orange;
                                collectibleUserData = ORANGE_COLLECTIBLE_ID;
                                texturePtr = &collectibleTextures[1];
                            } else if (typeRoll < magentaCollectibleProb + orangeCollectibleProb + greenCollectibleProb) {
                                type = CollectibleType::Green;
                                collectibleUserData = GREEN_COLLECTIBLE_ID;
                                texturePtr = &collectibleTextures[2];
                            } else if (typeRoll < magentaCollectibleProb + orangeCollectibleProb + greenCollectibleProb + redCollectibleProb) {
                                type = CollectibleType::Red;
                                collectibleUserData = RED_COLLECTIBLE_ID;
                                texturePtr = &collectibleTextures[3];
                            } else if (typeRoll < magentaCollectibleProb + orangeCollectibleProb + greenCollectibleProb + redCollectibleProb + whiteCollectibleProb) {
                                type = CollectibleType::White;
                                collectibleUserData = WHITE_COLLECTIBLE_ID;
                                texturePtr = &collectibleTextures[4];
                            } else {
                                type = CollectibleType::MinusScore;
                                collectibleUserData = MINUS_SCORE_COLLECTIBLE_ID;
                                texturePtr = &collectibleTextures[5];
                            }

                            newCollectible.type = type;
                            newCollectible.sprite.setTexture(*texturePtr);
                            newCollectible.sprite.setScale(
                                (collectibleRadius * 2.f) / newCollectible.sprite.getTexture()->getSize().x,
                                (collectibleRadius * 2.f) / newCollectible.sprite.getTexture()->getSize().y
                            );
                            newCollectible.sprite.setOrigin(newCollectible.sprite.getTexture()->getSize().x / 2.f, newCollectible.sprite.getTexture()->getSize().y / 2.f);
                            newCollectible.sprite.setPosition(collectiblePos);

                            b2BodyDef collectibleBodyDef;
                            collectibleBodyDef.type = b2_kinematicBody;
                            collectibleBodyDef.position = toMeters(collectiblePos);
                            newCollectible.body = world.CreateBody(&collectibleBodyDef);

                            b2CircleShape collectibleCircle;
                            collectibleCircle.m_radius = toMeters(sf::Vector2f(collectibleRadius, 0)).x;

                            b2FixtureDef collectibleFixtureDef;
                            collectibleFixtureDef.shape = &collectibleCircle;
                            collectibleFixtureDef.isSensor = true;
                            collectibleFixtureDef.userData.pointer = collectibleUserData;
                            newCollectible.body->CreateFixture(&collectibleFixtureDef);

                            
                            newCollectible.body->SetLinearVelocity(newBlock.body->GetLinearVelocity());

                            collectibles.push_back(newCollectible);
                        }
}

void MultiModeCollectibleSpawn(sf::Vector2f spawnPos, Block newBlock)
{
    float collectibleRoll = collectibleTypeDist(gen);
                    if (collectibleRoll < collectibleSpawnChanceMulti) {
                        Collectible newCollectible;
                        sf::Vector2f collectiblePos = spawnPos;
                        collectiblePos.y -= (fixedHeight / 2.f + collectibleRadius + 5.f); 

                        float typeRoll = collectibleTypeDist(gen);
                        uintptr_t collectibleUserData = 0;
                        sf::Texture* texturePtr = nullptr;
                        CollectibleType type;


                        if (typeRoll < greenCollectibleProbMulti) {
                            type = CollectibleType::Green;
                            collectibleUserData = GREEN_COLLECTIBLE_ID;
                            texturePtr = &collectibleTextures[2];
                        } else if (typeRoll < greenCollectibleProbMulti + redCollectibleProbMulti) {
                            type = CollectibleType::Red;
                            collectibleUserData = RED_COLLECTIBLE_ID;
                            texturePtr = &collectibleTextures[3];
                        }

                        newCollectible.type = type;
                        newCollectible.sprite.setTexture(*texturePtr);
                        newCollectible.sprite.setScale(
                            (collectibleRadius * 2.f) / newCollectible.sprite.getTexture()->getSize().x,
                            (collectibleRadius * 2.f) / newCollectible.sprite.getTexture()->getSize().y
                        );
                        newCollectible.sprite.setOrigin(newCollectible.sprite.getTexture()->getSize().x / 2.f, newCollectible.sprite.getTexture()->getSize().y / 2.f);
                        newCollectible.sprite.setPosition(collectiblePos);

                        b2BodyDef collectibleBodyDef;
                        collectibleBodyDef.type = b2_kinematicBody;
                        collectibleBodyDef.position = toMeters(collectiblePos);
                        newCollectible.body = world.CreateBody(&collectibleBodyDef);

                        b2CircleShape collectibleCircle;
                        collectibleCircle.m_radius = toMeters(sf::Vector2f(collectibleRadius, 0)).x;

                        b2FixtureDef collectibleFixtureDef;
                        collectibleFixtureDef.shape = &collectibleCircle;
                        collectibleFixtureDef.isSensor = true;
                        collectibleFixtureDef.userData.pointer = collectibleUserData;
                        newCollectible.body->CreateFixture(&collectibleFixtureDef);

                        
                        newCollectible.body->SetLinearVelocity(newBlock.body->GetLinearVelocity());

                        collectibles.push_back(newCollectible);
                    }
} 


