#include "ContactListener.hpp"
#include "../components/CharacterControlComponent.hpp"
#include "../components/CollisionResponseComponent.hpp"
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
        auto infoA = static_cast<CollisionInfo*>(bodyA);
        auto infoB = static_cast<CollisionInfo*>(bodyB);
        if (m_ecs.has<CollisionResponseComponent>(infoA->entity)) {
            m_ecs.get<CollisionResponseComponent>(infoA->entity)
                .collisions.emplace_back(infoB->entity, infoB->klass);
        } else {
            m_ecs.emplace<CollisionResponseComponent>(infoA->entity)
                .collisions.emplace_back(infoB->entity, infoB->klass);
        }
        if (m_ecs.has<CollisionResponseComponent>(infoB->entity)) {
            m_ecs.get<CollisionResponseComponent>(infoB->entity)
                .collisions.emplace_back(infoA->entity, infoA->klass);
        } else {
            m_ecs.emplace<CollisionResponseComponent>(infoB->entity)
                .collisions.emplace_back(infoA->entity, infoA->klass);
        }
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