#include "MovingPlatformSystem.hpp"
#include "../components/MovingPlatformComponent.hpp"
#include "../components/PhysicsComponent.hpp"
#include "../utility/GameFactory.hpp"
#include "../utility/Physics.hpp"
#include "SFML/System/Vector2.hpp"

namespace doode {

void MovingPlatformSystem::update(f32 p_delta, entt::registry& p_ecs) {
    p_ecs.view<MovingPlatformComponent, PhysicsComponent>().each(
        [p_delta](MovingPlatformComponent& p_platform,
                  PhysicsComponent& p_physical) {
            auto coef = p_platform.upwards ? -1.0F : 1.0F;

            auto delta =
                sf::Vector2f(0, p_platform.unitsPerSecond * p_delta) * coef;
            auto pos = Physics::toSfml(p_physical.body->GetPosition());
            pos += delta;
            p_physical.body->SetTransform(Physics::toBox2d(pos), 0);
            for (auto character : p_platform.occupants) {
                auto p = Physics::toSfml(character->GetPosition());
                p += delta;
                character->SetTransform(Physics::toBox2d(p), 0);
            }

            if (p_platform.upwards) {
                if (pos.y < p_platform.top.y) {
                    pos.y = p_platform.top.y;
                    p_platform.upwards = false;
                }
            } else {
                if (pos.y > p_platform.top.y + p_platform.size) {
                    pos.y = p_platform.top.y + p_platform.size;
                    p_platform.upwards = true;
                }
            }
        });
}

} // namespace doode