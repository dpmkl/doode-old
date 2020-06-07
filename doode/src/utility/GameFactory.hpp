#ifndef __DOODE_GAMEFACTORY_HPP__
#define __DOODE_GAMEFACTORY_HPP__

#include <box2d/box2d.h>
#include <entt/entt.hpp>

namespace doode {

class GameFactory {
public:
    static auto createCharacter(entt::entity p_entity, b2World& p_world)
        -> b2Body*;
    static void createPlayer(entt::registry& p_ecs, b2World& p_world);
};

} // namespace doode

#endif