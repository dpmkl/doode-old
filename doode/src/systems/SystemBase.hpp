#ifndef __DOODE_RENDERSYSTEMBASE_HPP__
#define __DOODE_RENDERSYSTEMBASE_HPP__

#include "../Types.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <entt/entt.hpp>

namespace doode {

class RenderSystemBase {
public:
    virtual void render(sf::RenderTarget& p_renderTarget) = 0;
};

class UpdateSystemBase {
public:
    virtual void update(entt::registry& p_ecs, f32 p_delta) = 0;
};

} // namespace doode

#endif