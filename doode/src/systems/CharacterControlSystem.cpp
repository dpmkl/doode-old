#include "CharacterControlSystem.hpp"
#include "../Services.hpp"
#include "../components/CharacterControlComponent.hpp"

namespace doode {

void CharacterControlSystem::update(f32 /*p_delta*/, entt::registry& p_ecs) {
    const auto& keyboard = Services::Keyboard::ref();
    p_ecs.view<CharacterControlComponent>().each(
        [keyboard](auto /*entity*/, CharacterControlComponent& p_character) {
            if (keyboard.isPressed(sf::Keyboard::Space)) {
                p_character.jump();
            }
            if (keyboard.isDown(sf::Keyboard::Left) && !p_character.onLeft) {
                p_character.strafe(-1.F);
            } else if (keyboard.isDown(sf::Keyboard::Right) &&
                       !p_character.onRight) {
                p_character.strafe(1.0F);
            } else {
                p_character.strafe(0.0F);
            }
        });
}

} // namespace doode