#ifndef __DOODE_PHYSICS_HPP__
#define __DOODE_PHYSICS_HPP__

#include "../Types.hpp"
#include "SFML/System/Vector2.hpp"
#include "box2d/b2_math.h"
#include <box2d/box2d.h>
#include <entt/entt.hpp>

namespace doode {

enum class CollisionType { Body, Feet, SensorLeft, SensorRight };

struct CollisionInfo {
    CollisionType type;
    entt::entity entity;
};

class Physics {
public:
    static constexpr f32 SCALE = 96.0F;

    static auto toBox2d(const sf::Vector2f& p_vector) -> b2Vec2;
    static auto toSfml(const b2Vec2& p_vector) -> sf::Vector2f;
};

} // namespace doode

#endif