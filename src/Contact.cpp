#include "../headers/Contact.hpp"
#include "../headers/Utility.hpp"

PlayerContactListener::PlayerContactListener(std::vector<b2Body*>& bodiesToRemove) : collectiblesToRemove(bodiesToRemove) {}

void PlayerContactListener::ContactBegin(const unsigned int windowWidth, const unsigned int windowHeight)
{
    b2Vec2 gravity(0.0f, 7.0f);
    b2World world(gravity);
    
    std::vector<b2Body*> collectiblesToRemoveFromWorld;
    PlayerContactListener contactListener(collectiblesToRemoveFromWorld);
    world.SetContactListener(&contactListener);

    b2BodyDef ceilingBodyDef;
    ceilingBodyDef.position.Set(toMeters(sf::Vector2f(windowWidth / 2.f, -10.f)).x, toMeters(sf::Vector2f(windowWidth / 2.f, -10.f)).y);
    b2Body* ceilingBody = world.CreateBody(&ceilingBodyDef);
    b2PolygonShape ceilingBox;
    ceilingBox.SetAsBox(toMeters(sf::Vector2f(windowWidth / 2.f, 10.f)).x, toMeters(sf::Vector2f(windowWidth / 2.f, 10.f)).y);
    b2Fixture* ceilingFixture = ceilingBody->CreateFixture(&ceilingBox, 0.0f);
    ceilingFixture->GetUserData().pointer = CEILING_ID;

}

void PlayerContactListener::BeginContact(b2Contact* contact) {
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();
    uintptr_t userDataA = fixtureA->GetUserData().pointer;
    uintptr_t userDataB = fixtureB->GetUserData().pointer;

    // Platform Contact via Foot Sensor
    checkFootContact(userDataA, userDataB, +1);
    checkFootContact(userDataB, userDataA, +1);

    // Collectibles
    if ((userDataA == PLAYER1_ID && isCollectible(userDataB)) ||
        (userDataB == PLAYER1_ID && isCollectible(userDataA))) {
        b2Body* collectibleBody = (userDataA == PLAYER1_ID) ? fixtureB->GetBody() : fixtureA->GetBody();
        collectiblesToRemove.push_back(collectibleBody);
    }
    if ((userDataA == PLAYER2_ID && isCollectible(userDataB)) ||
        (userDataB == PLAYER2_ID && isCollectible(userDataA))) {
        b2Body* collectibleBody = (userDataA == PLAYER2_ID) ? fixtureB->GetBody() : fixtureA->GetBody();
        collectiblesToRemove.push_back(collectibleBody);
}
}

void PlayerContactListener::EndContact(b2Contact* contact) {
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();
    uintptr_t userDataA = fixtureA->GetUserData().pointer;
    uintptr_t userDataB = fixtureB->GetUserData().pointer;

    checkFootContact(userDataA, userDataB, -1);
    checkFootContact(userDataB, userDataA, -1);

}

void PlayerContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();
    uintptr_t userDataA = fixtureA->GetUserData().pointer;
    uintptr_t userDataB = fixtureB->GetUserData().pointer;

    if (((userDataA == PLAYER1_ID || userDataA == PLAYER2_ID) && userDataB >= PLATFORM_ID_BASE) ||
        ((userDataB == PLAYER1_ID || userDataB == PLAYER2_ID) && userDataA >= PLATFORM_ID_BASE)) {
        contact->SetFriction(0.0f);
    }
}

bool PlayerContactListener::isGrounded(uintptr_t playerId) const {
    auto it = footContactsMap.find(playerId);
    return (it != footContactsMap.end() && it->second > 0);
}

void PlayerContactListener::reset() {
    footContactsMap.clear();
    touchedGroundMap.clear();
    collectiblesToRemove.clear();
}

void PlayerContactListener::checkFootContact(uintptr_t footSensorId, uintptr_t otherId, int change) {
    if ((footSensorId == FOOT_SENSOR_PLAYER1 || footSensorId == FOOT_SENSOR_PLAYER2) &&
        otherId >= PLATFORM_ID_BASE) {
        
        uintptr_t ownerId = (footSensorId == FOOT_SENSOR_PLAYER1) ? PLAYER1_ID : PLAYER2_ID;
        footContactsMap[ownerId] += change;

        // Avoid negative counts
        if (footContactsMap[ownerId] < 0) footContactsMap[ownerId] = 0;
    }
}

bool PlayerContactListener::isCollectible(uintptr_t id) const {
    return (id == MAGENTA_COLLECTIBLE_ID || id == ORANGE_COLLECTIBLE_ID ||
            id == GREEN_COLLECTIBLE_ID || id == RED_COLLECTIBLE_ID ||
            id == WHITE_COLLECTIBLE_ID || id == MINUS_SCORE_COLLECTIBLE_ID);
}