#ifndef __DOODE_RENDERSYSTEMBASE_HPP__
#define __DOODE_RENDERSYSTEMBASE_HPP__

#include "../Services.hpp"
#include "../Types.hpp"
#include "SFML/Window/Event.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <entt/entt.hpp>

namespace doode {

class RenderSystemBase {
public:
    virtual void render(sf::RenderTarget& p_renderTarget,
                        entt::registry& p_ecs) = 0;
};

class UpdateSystemBase {
public:
    virtual void update(f32 p_delta, entt::registry& p_ecs) = 0;
};

class EventSystemBase {
public:
    virtual void event(const sf::Event& p_event, entt::registry& p_ecs) = 0;
};

} // namespace doode

#endif