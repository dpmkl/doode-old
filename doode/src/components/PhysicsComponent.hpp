#ifndef __DOODE_PHYSICSCOMPONENT_HPP__
#define __DOODE_PHYSICSCOMPONENT_HPP__

#include "box2d/b2_body.h"
#include <box2d/box2d.h>

namespace doode {

struct PhysicsComponent {
    PhysicsComponent(b2Body* p_body) : body(p_body) {}
    b2Body* body;
};

} // namespace doode

#endif