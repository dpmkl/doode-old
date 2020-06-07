#include "Physics.hpp"
#include "SFML/System/Vector2.hpp"
#include "box2d/b2_math.h"

namespace doode {

auto Physics::toBox2d(const sf::Vector2f& p_vector) -> b2Vec2 {
    return b2Vec2(p_vector.x / SCALE, p_vector.y / SCALE);
}

auto Physics::toSfml(const b2Vec2& p_vector) -> sf::Vector2f {
    return sf::Vector2f(p_vector.x * SCALE, p_vector.y * SCALE);
}

} // namespace doode