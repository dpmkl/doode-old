#ifndef __DOODE_BOX2DRENDERSYSTEM_HPP__
#define __DOODE_BOX2DRENDERSYSTEM_HPP__

#include "../Types.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SystemBase.hpp"
#include "box2d/b2_draw.h"
#include <box2d/box2d.h>

namespace doode {

class Box2dRenderer : public b2Draw {
public:
    Box2dRenderer(sf::RenderTarget& p_renderTarget)
        : m_renderTarget(p_renderTarget) {}

    void DrawPolygon(const b2Vec2* p_vertices, i32 p_vertexCount,
                     const b2Color& p_color) override;
    void DrawSolidPolygon(const b2Vec2* p_vertices, i32 p_vertexCount,
                          const b2Color& p_color) override;
    void DrawCircle(const b2Vec2& p_center, f32 p_radius,
                    const b2Color& p_color) override;
    void DrawSolidCircle(const b2Vec2& p_center, f32 p_radius,
                         const b2Vec2& p_axis, const b2Color& p_color) override;
    void DrawSegment(const b2Vec2& p_p1, const b2Vec2& p_p2,
                     const b2Color& p_color) override;
    void DrawTransform(const b2Transform& p_xf) override;
    void DrawPoint(const b2Vec2& p_p, f32 p_size,
                   const b2Color& p_color) override;

    void update(sf::RenderTarget& p_renderTarget);

private:
    sf::RenderTarget& m_renderTarget;
};

struct Box2dRenderSystem : RenderSystemBase {
    Box2dRenderSystem();
    void render(sf::RenderTarget& p_renderTarget,
                entt::registry& p_ecs) override;

private:
    std::unique_ptr<Box2dRenderer> m_box2d;
};

} // namespace doode

#endif