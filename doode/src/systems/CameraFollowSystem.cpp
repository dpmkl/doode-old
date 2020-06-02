#include "CameraFollowSystem.hpp"
#include "../Physics.hpp"
#include "../components/CharacterControlComponent.hpp"
#include "../components/Tags.hpp"

namespace doode {

void CameraFollowSystem::render(sf::RenderTarget& p_renderTarget,
                                entt::registry& p_ecs) {
    p_ecs.view<CharacterControlComponent, CameraFollow>().each(
        [&p_renderTarget](auto, auto& p_character) {
            auto view = p_renderTarget.getView();
            view.setCenter(Physics::toSfml(p_character.body->GetPosition()));
            p_renderTarget.setView(view);
        });
}

} // namespace doode