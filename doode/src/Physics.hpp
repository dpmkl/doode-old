#ifndef __DOODE_PHYSICS_HPP__
#define __DOODE_PHYSICS_HPP__

#include "SFML/System/Vector2.hpp"
#include "Types.hpp"
#include "box2d/b2_math.h"
#include <box2d/box2d.h>

namespace doode {

class Physics {
public:
    static constexpr f32 SCALE = 96.0F;

    static auto toBox2d(const sf::Vector2f& p_vector) -> b2Vec2;
    static auto toSfml(const b2Vec2& p_vector) -> sf::Vector2f;
};

} // namespace doode

#endif