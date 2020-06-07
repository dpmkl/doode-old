#ifndef __DOODE_MOVINGPLATFORMSYSTEM_HPP__
#define __DOODE_MOVINGPLATFORMSYSTEM_HPP__

#include "SystemBase.hpp"

namespace doode {

class MovingPlatformSystem : public UpdateSystemBase {
public:
    void update(f32 p_delta, entt::registry& p_ecs) override;
};

} // namespace doode

#endif