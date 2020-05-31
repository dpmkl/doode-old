#include "PhysicsSystem.hpp"

namespace doode {

void PhysicsSystem::update(f32 p_delta, entt::registry& /*p_ecs*/) {
    Services::Physics::ref().Step(p_delta, 4, 2);
}

} // namespace doode