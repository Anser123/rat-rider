#include "../headers/Platform.hpp"
#include "../headers/Game.hpp"

void PlatformSpawn()
{
    Block initialBlock;
    float initialBlockLength = windowWidth - 250.f ;
    sf::Vector2f initialSpawnPos(windowWidth / 2.f, windowHeight - 500.f);
    initialBlock.shape.setSize(sf::Vector2f(initialBlockLength, fixedHeight));
    initialBlock.shape.setFillColor(defaultBlockColor);
    initialBlock.shape.setOutlineColor(sf::Color::Black);
    initialBlock.shape.setOutlineThickness(2.5f);
    initialBlock.shape.setOrigin(initialBlockLength / 2.f, fixedHeight / 2.f);
    initialBlock.shape.setPosition(initialSpawnPos);
    initialBlock.line.setSize(sf::Vector2f(15.f, 500));
    initialBlock.line.setFillColor(sf::Color(150,150,150));
    initialBlock.line.setOutlineColor(sf::Color::Black);
    initialBlock.line.setOutlineThickness(2.5f);
    initialBlock.line.setOrigin(7.5f, 0.f);
    initialBlock.line.setPosition(initialSpawnPos.x, initialSpawnPos.y + fixedHeight / 2.f);

    b2BodyDef initialBlockBodyDef;
    initialBlockBodyDef.type = b2_kinematicBody;
    initialBlockBodyDef.position = toMeters(initialSpawnPos);
    initialBlock.body = world.CreateBody(&initialBlockBodyDef);
    initialBlock.id = nextPlatformId++;

    b2PolygonShape initialBlockBox;
    initialBlockBox.SetAsBox(toMeters(sf::Vector2f(initialBlockLength / 2.f, fixedHeight / 2.f)).x, toMeters(sf::Vector2f(initialBlockLength / 2.f, fixedHeight / 2.f)).y);
    b2FixtureDef initialBlockFixtureDef;
    initialBlockFixtureDef.shape = &initialBlockBox;
    initialBlockFixtureDef.friction = 0.7f;
    initialBlockFixtureDef.userData.pointer = initialBlock.id;
    initialBlock.body->CreateFixture(&initialBlockFixtureDef);

    // Set initial block velocity to move left
    initialBlock.body->SetLinearVelocity(b2Vec2(toMeters(sf::Vector2f(-blockSpeed, 0.f)).x, 0.0f));
    blocks.push_back(initialBlock);
}

void PlatformRemoval()
{
    for (auto& block : blocks) {
        if (block.body) {
            block.shape.setPosition(toPixels(block.body->GetPosition()));
            block.line.setPosition(block.shape.getPosition().x, block.shape.getPosition().y + fixedHeight / 2.f);
            if (block.shape.getPosition().x < -block.shape.getSize().x / 2.f) {
                block.markedForRemoval = true;
            }
        }
    }
}

void PlatformErase()
{
    blocks.erase(std::remove_if(blocks.begin(), blocks.end(), [&](Block& block) {
        if (block.markedForRemoval && block.body) {
            world.DestroyBody(block.body);
            block.body = nullptr;
            return true;
        }
        return false;
    }), blocks.end());
}


void PlatformSpeed(float dt)
{
    if (blockSpeed < maxBlockSpeed) {
        blockSpeed += blockSpeedIncreaseFactor * dt;
        blockSpeed = std::min(blockSpeed, maxBlockSpeed);
        
        float speedRatio = (blockSpeed - 200.f) / (maxBlockSpeed - 200.f);
        minSpawnTime = lerp(2.5f, minSpawnTimeBase, speedRatio);
        maxSpawnTime = lerp(3.5f, maxSpawnTimeBase, speedRatio);
    }
}