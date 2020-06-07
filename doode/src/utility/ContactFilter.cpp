#include "ContactFilter.hpp"
#include "../components/CharacterControlComponent.hpp"
#include "../components/CollisionResponseComponent.hpp"
#include "../components/MovingPlatformComponent.hpp"
#include "../components/PhysicsComponent.hpp"
#include "Physics.hpp"

namespace doode {

ContactFilter::ContactFilter(entt::registry& p_ecs) : m_ecs(p_ecs) {}

auto ContactFilter::ShouldCollide(b2Fixture* p_a, b2Fixture* p_b) -> bool {
    auto userA = p_a->GetUserData();
    auto userB = p_b->GetUserData();
    if (userA != nullptr && userB != nullptr) {
        auto iA = static_cast<CollisionInfo*>(userA);
        auto iB = static_cast<CollisionInfo*>(userB);
        if ((iA->type == CollisionType::Platform &&
             iB->type == CollisionType::Body) ||
            (iB->type == CollisionType::Platform &&
             iA->type == CollisionType::Body)) {
            return false;
        }

        if ((iA->type == CollisionType::Platform &&
             iB->type == CollisionType::Feet) ||
            (iB->type == CollisionType::Platform &&
             iA->type == CollisionType::Feet)) {

            auto characterInfo = iA->type == CollisionType::Feet ? iA : iB;
            auto& character =
                m_ecs.get<CharacterControlComponent>(characterInfo->entity);
            auto velC = character.body->GetLinearVelocity();
            if (velC.y < 0 || character.dropping) {
                return false;
            }
        }
    }
    return true;
}

} // namespace doode