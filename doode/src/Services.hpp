#ifndef __DOODE_SERVICES_HPP__
#define __DOODE_SERVICES_HPP__

#include <box2d/box2d.h>
#include <entt/entt.hpp>

namespace doode {
struct Services {
    using Ecs = entt::service_locator<entt::registry>;
    using Physics = entt::service_locator<b2World>;
};

} // namespace doode

#endif