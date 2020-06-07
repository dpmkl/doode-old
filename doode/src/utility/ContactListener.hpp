#ifndef __DOODE_CONTACTLISTENER_HPP__
#define __DOODE_CONTACTLISTENER_HPP__

#include "Physics.hpp"
#include "box2d/b2_fixture.h"
#include <box2d/box2d.h>
#include <entt/entt.hpp>

namespace doode {

class ContactListener : public b2ContactListener {
public:
    ContactListener(entt::registry& p_ecs);

    void BeginContact(b2Contact* p_contact) override;

    void EndContact(b2Contact* p_contact) override;

private:
    void evaluateCharacter(CollisionInfo* p_info, bool p_value);

    entt::registry& m_ecs;
};

} // namespace doode

#endif