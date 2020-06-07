#ifndef __DOODE_CONTACTFILTER_HPP__
#define __DOODE_CONTACTFILTER_HPP__

#include <box2d/box2d.h>
#include <entt/entt.hpp>

namespace doode {

class ContactFilter : public b2ContactFilter {
public:
    ContactFilter(entt::registry& p_ecs);
    auto ShouldCollide(b2Fixture* p_a, b2Fixture* p_b) -> bool override;

private:
    entt::registry& m_ecs;
};

} // namespace doode

#endif