#ifndef __DOODE_INPUTCONTROLCOMPONENT_HPP__
#define __DOODE_INPUTCONTROLCOMPONENT_HPP__

#include "../Physics.hpp"
#include "../Types.hpp"
#include "SFML/System/Vector2.hpp"
#include "box2d/b2_body.h"
#include "box2d/b2_math.h"
#include <box2d/box2d.h>
#include <string>

namespace doode {

constexpr f32 JUMP_FORCE = -64.0F;
constexpr f32 STRAFE_FORCE = 16.0F;
constexpr f32 STRAFE_COEF = 0.8F;
constexpr f32 STRAFE_MAX = 2.8F;

struct CharacterControlComponent {
    CharacterControlComponent(b2Body* p_body) : body(p_body), onGround(false) {}
    b2Body* body;
    bool onGround;

    void jump() {
        auto force = Physics::toBox2d(sf::Vector2f(0, JUMP_FORCE));
        body->ApplyLinearImpulseToCenter(force, true);
    }

    void strafe(f32 p_val) {
        if (p_val == 0.0F) {
            auto vel = body->GetLinearVelocity();
            body->SetLinearVelocity(b2Vec2(vel.x * STRAFE_COEF, vel.y));
        } else {
            auto force =
                Physics::toBox2d(sf::Vector2f(STRAFE_FORCE * p_val, 0));
            body->ApplyLinearImpulseToCenter(force, true);
        }
        auto vel = body->GetLinearVelocity();
        vel.x = vel.x > 0 ? std::min(STRAFE_MAX, vel.x)
                          : std::max(-STRAFE_MAX, vel.x);
        body->SetLinearVelocity(vel);
    }
};

} // namespace doode

#endif