#ifndef __DOODE_CHARACTERCONTROLSYSTEM_HPP__
#define __DOODE_CHARACTERCONTROLSYSTEM_HPP__

#include "SystemBase.hpp"

namespace doode {

class CharacterControlSystem : public UpdateSystemBase {
public:
    void update(f32 p_delta, entt::registry& p_ecs) override;
};

} // namespace doode

#endif