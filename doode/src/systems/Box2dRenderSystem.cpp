#include "Box2dRenderSystem.hpp"
#include <memory>

namespace doode {

void Box2dRenderer::DrawPolygon(const b2Vec2* p_vertices, i32 p_vertexCount,
                                const b2Color& p_color) {}
void Box2dRenderer::DrawSolidPolygon(const b2Vec2* p_vertices,
                                     i32 p_vertexCount,
                                     const b2Color& p_color) {}
void Box2dRenderer::DrawCircle(const b2Vec2& p_center, f32 p_radius,
                               const b2Color& p_color) {}
void Box2dRenderer::DrawSolidCircle(const b2Vec2& p_center, f32 p_radius,
                                    const b2Vec2& p_axis,
                                    const b2Color& p_color) {}
void Box2dRenderer::DrawSegment(const b2Vec2& p_p1, const b2Vec2& p_p2,
                                const b2Color& p_color) {}
void Box2dRenderer::DrawTransform(const b2Transform& p_xf) {}
void Box2dRenderer::DrawPoint(const b2Vec2& p_p, f32 p_size,
                              const b2Color& p_color) {}

void Box2dRenderer::update(sf::RenderTarget& p_renderTarget) {}

void Box2dRenderSystem::render(sf::RenderTarget& p_renderTarget,
                               entt::registry&) {
    auto& world = Services::Physics::ref();
    if (!m_box2d) {
        m_box2d = std::make_unique<Box2dRenderer>(p_renderTarget);
        world.SetDebugDraw(m_box2d.get());
    }
    world.DebugDraw();
}

} // namespace doode