#ifndef __DOODE_COLLISIONRESPONSECOMPONENT_HPP__
#define __DOODE_COLLISIONRESPONSECOMPONENT_HPP__

#include "../utility/Physics.hpp"
#include <vector>

namespace doode {

struct CollisionResponseComponent {
    std::vector<CollisionResult> collisions;
};

} // namespace doode

#endif