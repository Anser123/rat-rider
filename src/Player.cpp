#include "../headers/Player.hpp"
#include "../headers/Utility.hpp"
#include "../headers/ControlRoom.hpp"
#include "../headers/Textures.hpp"
#include "../headers/Game.hpp"

void PlayerPosUpdate()
{
    if (playerBody) playerSprite.setPosition(toPixels(playerBody->GetPosition()));
    if (player2Body) player2Sprite.setPosition(toPixels(player2Body->GetPosition()));
    
}

void Player1Spawn()
{
    b2BodyDef playerBodyDef;
    playerBodyDef.type = b2_dynamicBody;
    playerBodyDef.position = toMeters(sf::Vector2f(windowWidth / 4.f, windowHeight - 600.f));
    playerBodyDef.fixedRotation = true;
    playerBodyDef.allowSleep = false;
    playerBody = world.CreateBody(&playerBodyDef);

    b2PolygonShape playerBox;
    playerBox.SetAsBox(toMeters(sf::Vector2f(playerWidth / 2.f, playerHeight / 2.f)).x, toMeters(sf::Vector2f(playerWidth / 2.f, playerHeight / 2.f)).y);
    b2FixtureDef playerFixtureDef;
    playerFixtureDef.shape = &playerBox;
    playerFixtureDef.density = 1.0f;
    playerFixtureDef.friction = 0.5f;
    playerFixtureDef.restitution = 0.0f;
    playerFixtureDef.userData.pointer = PLAYER1_ID;
    playerBody->CreateFixture(&playerFixtureDef);

    b2PolygonShape footSensorBox;
    b2Vec2 footSensorCenter = b2Vec2(0, toMeters(sf::Vector2f(0, playerHeight / 2.f)).y);
    footSensorBox.SetAsBox(toMeters(sf::Vector2f(playerWidth / 2.f * 0.9f, 5.f)).x, toMeters(sf::Vector2f(playerWidth / 2.f * 0.9f, 5.f)).y, footSensorCenter, 0);
    b2FixtureDef footSensorFixtureDef;
    footSensorFixtureDef.shape = &footSensorBox;
    footSensorFixtureDef.isSensor = true;
    footSensorFixtureDef.userData.pointer = FOOT_SENSOR_PLAYER1;
    playerBody->CreateFixture(&footSensorFixtureDef);

    playerSprite.setTexture(staticPlayerTexture);
    playerSprite.setTexture(staticPlayerTexture2);
    jumpsRemaining = maxJumps;
    fastFallActive = false;
    player1Alive = true;
    playerAnimClock.restart();
}

void Player2Spawn()
{

    b2BodyDef player2BodyDef;
    player2BodyDef.type = b2_dynamicBody;
    player2BodyDef.position = toMeters(sf::Vector2f(windowWidth / 4.f - 100.f, windowHeight - 600.f));
    player2BodyDef.fixedRotation = true;
    player2BodyDef.allowSleep = false;
    player2Body = world.CreateBody(&player2BodyDef);

    b2PolygonShape player2Box;
    player2Box.SetAsBox(toMeters(sf::Vector2f(playerWidth / 2.f, playerHeight / 2.f)).x, toMeters(sf::Vector2f(playerWidth / 2.f, playerHeight / 2.f)).y);
    b2FixtureDef player2FixtureDef;
    player2FixtureDef.shape = &player2Box;
    player2FixtureDef.density = 1.0f;
    player2FixtureDef.friction = 0.5f;
    player2FixtureDef.restitution = 0.0f;
    player2FixtureDef.userData.pointer = PLAYER2_ID;
    player2Body->CreateFixture(&player2FixtureDef);

    b2PolygonShape footSensor2Box;
    b2Vec2 footSensor2Center = b2Vec2(0, toMeters(sf::Vector2f(0, playerHeight / 2.f)).y);
    footSensor2Box.SetAsBox(toMeters(sf::Vector2f(playerWidth / 2.f * 0.9f, 5.f)).x, toMeters(sf::Vector2f(playerWidth / 2.f * 0.9f, 5.f)).y, footSensor2Center, 0);
    b2FixtureDef footSensor2FixtureDef;
    footSensor2FixtureDef.shape = &footSensor2Box;
    footSensor2FixtureDef.isSensor = true;
    footSensor2FixtureDef.userData.pointer = FOOT_SENSOR_PLAYER2;
    player2Body->CreateFixture(&footSensor2FixtureDef);

    player2Sprite.setTexture(staticPlayer2Texture);
    player2Sprite.setTexture(staticPlayer2Texture2);
    jumpsRemaining2 = maxJumps;
    fastFallActive2 = false;
    player2Alive = true;
    player2AnimClock.restart();
}


void Player1Jump()
{
    JumpSound.play();
    float impulseMagnitude = playerJumpForce * METERS_PER_PIXEL * playerBody->GetMass();
    playerBody->ApplyLinearImpulseToCenter(b2Vec2(0, -impulseMagnitude), true);
    jumpsRemaining--;

}

void Player2Jump()
{
    JumpSound.play();
    float impulseMagnitude = playerJumpForce * METERS_PER_PIXEL * player2Body->GetMass();
    player2Body->ApplyLinearImpulseToCenter(b2Vec2(0, -impulseMagnitude), true);
    jumpsRemaining2--;
}

void Player1Fall()
{
    if (playerBody) {
        if (fastFallActive && !contactListener.isGrounded(PLAYER1_ID)) {
            FallSound.play();
            playerBody->SetGravityScale(fastFallGravityScale);
        } else {
            playerBody->SetGravityScale(1.0f);
        }
    }
}

void Player2Fall()
{
    if (player2Body) {
        if (fastFallActive2 && !contactListener.isGrounded(PLAYER2_ID)) {
            FallSound.play();
            player2Body->SetGravityScale(fastFallGravityScale);
        } else {
            player2Body->SetGravityScale(1.0f);
        }
    }

}
