#ifndef __DOODE_CAMERAFOLLOWSYSTEM_HPP__
#define __DOODE_CAMERAFOLLOWSYSTEM_HPP__

#include "SystemBase.hpp"

namespace doode {

class CameraFollowSystem : public RenderSystemBase {
public:
    void render(sf::RenderTarget& p_renderTarget,
                entt::registry& p_ecs) override;
};

} // namespace doode

#endif