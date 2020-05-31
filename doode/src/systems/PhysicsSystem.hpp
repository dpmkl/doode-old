#ifndef __DOODE_PHYSICSSYSTEM_HPP__
#define __DOODE_PHYSICSSYSTEM_HPP__

#include "SystemBase.hpp"

namespace doode {

class PhysicsSystem : public UpdateSystemBase {
    void update(f32 p_delta, entt::registry& p_ecs) override;
};

} // namespace doode

#endif