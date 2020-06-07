#ifndef __DOODE_INPUTCONTROLCOMPONENT_HPP__
#define __DOODE_INPUTCONTROLCOMPONENT_HPP__

#include "../Types.hpp"
#include "../utility/GameFactory.hpp"
#include "../utility/Physics.hpp"
#include "SFML/System/Vector2.hpp"
#include "box2d/b2_body.h"
#include "box2d/b2_math.h"
#include "spdlog/common.h"
#include <box2d/box2d.h>
#include <set>
#include <spdlog/spdlog.h>
#include <string>
namespace doode {

constexpr f32 JUMP_FORCE = -96.0F;
constexpr f32 STRAFE_FORCE = 16.0F;
constexpr f32 STRAFE_COEF = 0.8F;
constexpr f32 STRAFE_MAX = 2.8F;

struct CharacterControlComponent {
    CharacterControlComponent(b2Body* p_body)
        : body(p_body), onGround(false), onLeft(false), onRight(false),
          dropping(false), jumpCount(0), onPlatform(false) {}
    b2Body* body;
    bool onGround;
    bool onLeft;
    bool onRight;
    bool dropping;
    u32 jumpCount;
    bool onPlatform;

    void setOnGround() {
        onGround = true;
        dropping = false;
        jumpCount = 0;
        spdlog::info("On ground");
    }

    void jump() {
        spdlog::info("Jumping: " + std::to_string(onGround) + " " +
                     std::to_string(jumpCount));
        if (onGround && jumpCount < 3) {
            ++jumpCount;
            auto force =
                Physics::toBox2d(sf::Vector2f(0, JUMP_FORCE / jumpCount));
            body->ApplyLinearImpulseToCenter(force, true);
        }
    }

    void drop() {
        if (!dropping && onGround && onPlatform) {
            auto pos = Physics::toSfml(body->GetPosition());
            pos.y += game::WALL_HEIGHT * 2;
            body->SetTransform(Physics::toBox2d(pos), 0);
        }
        dropping = true;
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