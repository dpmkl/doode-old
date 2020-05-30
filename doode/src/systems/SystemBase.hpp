#ifndef __DOODE_RENDERSYSTEMBASE_HPP__
#define __DOODE_RENDERSYSTEMBASE_HPP__

#include "../Services.hpp"
#include "../Types.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <entt/entt.hpp>

namespace doode {

struct RenderSystemBase {
    virtual void render(sf::RenderTarget& p_renderTarget,
                        entt::registry& p_ecs) = 0;
};

struct UpdateSystemBase {
    virtual void update(f32 p_delta, entt::registry& p_ecs) = 0;
};

} // namespace doode

#endif