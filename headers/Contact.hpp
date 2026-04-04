#pragma once
#include "../masla.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <box2d/box2d.h>
#include <map>

static constexpr uintptr_t PLAYER1_ID = 0; 
static constexpr uintptr_t PLAYER2_ID = 10; 
const uintptr_t FOOT_SENSOR_PLAYER1 = 5001;
const uintptr_t FOOT_SENSOR_PLAYER2 = 5002;
static constexpr uintptr_t CEILING_ID = 3;
static constexpr uintptr_t MAGENTA_COLLECTIBLE_ID = 4;
static constexpr uintptr_t ORANGE_COLLECTIBLE_ID = 5;
static constexpr uintptr_t GREEN_COLLECTIBLE_ID = 6;
static constexpr uintptr_t RED_COLLECTIBLE_ID = 7;
static constexpr uintptr_t WHITE_COLLECTIBLE_ID = 8;
static constexpr uintptr_t MINUS_SCORE_COLLECTIBLE_ID = 9;
static constexpr uintptr_t PLATFORM_ID_BASE = 1000;


class PlayerContactListener : public b2ContactListener
 {
    public:
        
        std::map<uintptr_t, int> footContactsMap;
        std::map<uintptr_t, bool> touchedGroundMap;
        std::vector<b2Body*>& collectiblesToRemove;
        
        void ContactBegin(const unsigned int windowWidth, const unsigned int windowHeight);

        PlayerContactListener(std::vector<b2Body*>& bodiesToRemove);
    
        void BeginContact(b2Contact* contact) override;

        void EndContact(b2Contact* contact) override;

        void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override;

        bool isGrounded(uintptr_t playerId) const;

        void reset();
        
        void checkFootContact(uintptr_t footSensorId, uintptr_t otherId, int change);
    
        bool isCollectible(uintptr_t id) const;

    };
    
    
    