#include "ContactListener.hpp"
#include "../components/CharacterControlComponent.hpp"
#include "Physics.hpp"
#include "box2d/b2_fixture.h"

namespace doode {

ContactListener::ContactListener(entt::registry& p_ecs) : m_ecs(p_ecs) {}

void ContactListener::BeginContact(b2Contact* p_contact) {
    auto bodyA = p_contact->GetFixtureA()->GetUserData();
    auto bodyB = p_contact->GetFixtureB()->GetUserData();
    if (bodyA == nullptr && bodyB == nullptr) {
        return;
    } else if (bodyA != nullptr && bodyB != nullptr) {

    } else {
        auto body = bodyA != nullptr ? bodyA : bodyB;
        auto info = static_cast<CollisionInfo*>(body);
        if (info->type == CollisionType::SensorLeft ||
            info->type == CollisionType::SensorRight ||
            info->type == CollisionType::Feet) {
            evaluateCharacter(info, true);
        }
    }
}

void ContactListener::EndContact(b2Contact* p_contact) {
    auto bodyA = p_contact->GetFixtureA()->GetUserData();
    auto bodyB = p_contact->GetFixtureB()->GetUserData();
    if (bodyA == nullptr || bodyB == nullptr) {
        auto body = bodyA != nullptr ? bodyA : bodyB;
        auto info = static_cast<CollisionInfo*>(body);
        if (info->type == CollisionType::SensorLeft ||
            info->type == CollisionType::SensorRight ||
            info->type == CollisionType::Feet) {
            evaluateCharacter(info, false);
        }
    }
}

void ContactListener::evaluateCharacter(CollisionInfo* p_info, bool p_value) {
    auto& character = m_ecs.get<CharacterControlComponent>(p_info->entity);
    if (p_info->type == CollisionType::SensorLeft) {
        character.onLeft = p_value;
    } else if (p_info->type == CollisionType::SensorRight) {
        character.onRight = p_value;
    } else if (p_info->type == CollisionType::Feet) {
        character.onGround = p_value;
        if (p_value) {
            character.jumpCount = 0;
        }
    }
}

} // namespace doode