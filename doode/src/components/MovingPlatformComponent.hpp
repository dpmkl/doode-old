#ifndef __DOODE_MOVINGPLATFORMCOMPONENT_HPP__
#define __DOODE_MOVINGPLATFORMCOMPONENT_HPP__

#include "../Types.hpp"
#include "SFML/System/Vector2.hpp"
#include <SFML/System.hpp>
#include <box2d/box2d.h>
#include <set>

namespace doode {

struct MovingPlatformComponent {
    f32 unitsPerSecond;
    bool direction;
    sf::Vector2f upper;
    sf::Vector2f lower;
    std::set<b2Body*> occupants;
};

} // namespace doode

#endif