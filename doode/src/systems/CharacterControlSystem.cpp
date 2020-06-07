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
            if ((keyboard.isDown(sf::Keyboard::Left) ||
                 keyboard.isDown(sf::Keyboard::A)) &&
                !p_character.onLeft) {
                p_character.strafe(-1.F);
            } else if ((keyboard.isDown(sf::Keyboard::Right) ||
                        keyboard.isDown(sf::Keyboard::D)) &&
                       !p_character.onRight) {
                p_character.strafe(1.0F);
            } else {
                p_character.strafe(0.0F);
            }
            if (keyboard.isDown(sf::Keyboard::Down) ||
                keyboard.isDown(sf::Keyboard::S)) {
                p_character.drop();
            } else {
                p_character.dropping = false;
            }
        });
}

} // namespace doode