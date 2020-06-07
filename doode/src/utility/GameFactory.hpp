#ifndef __DOODE_GAMEFACTORY_HPP__
#define __DOODE_GAMEFACTORY_HPP__

#include "../Types.hpp"
#include "Maze.hpp"
#include "SFML/System/Vector2.hpp"
#include <box2d/box2d.h>
#include <entt/entt.hpp>

namespace doode {

class GameFactory {
public:
    static auto createCharacter(entt::entity p_entity, b2World& p_world)
        -> b2Body*;
    static void createPlayer(entt::registry& p_ecs, b2World& p_world);
    static void createStaticBlock(const sf::Vector2f& p_position,
                                  const sf::Vector2f& p_size, b2World& p_world);
    static void createPlatform(entt::registry& p_ecs, b2World& p_world,
                               const sf::Vector2f& p_position, f32 p_range);
    static auto createMaze(u32 p_size, u32 p_seed, b2World& p_world) -> Maze;
};

} // namespace doode

#endif