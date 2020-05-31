#include "Box2dRenderSystem.hpp"
#include "../Types.hpp"
#include "SFML/Config.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/ConvexShape.hpp"
#include "SFML/Graphics/PrimitiveType.hpp"
#include "SFML/System/Vector2.hpp"
#include <memory>

namespace doode {

Box2dRenderer::Box2dRenderer(sf::RenderTarget& p_renderTarget)
    : m_renderTarget(p_renderTarget) {
    Services::Physics::ref().SetDebugDraw(this);
}

auto Box2dRenderer::b2ToSfColor(const b2Color& p_color, u8 p_alpha)
    -> sf::Color {
    return sf::Color(static_cast<u8>(p_color.r * 0xff),
                     static_cast<u8>(p_color.g * 0xff),
                     static_cast<u8>(p_color.b * 0xff), p_alpha);
}

auto Box2dRenderer::b2ToSfVector(const b2Vec2& p_vector) -> sf::Vector2f {
    return sf::Vector2f(p_vector.x * SCALE, p_vector.y * SCALE);
}

void Box2dRenderer::DrawPolygon(const b2Vec2* p_vertices, i32 p_vertexCount,
                                const b2Color& p_color) {
    sf::ConvexShape poly(p_vertexCount);
    sf::Vector2f center;
    for (i32 i = 0; i < p_vertexCount; ++i) {
        sf::Vector2f vec = b2ToSfVector(p_vertices[i]);
        poly.setPoint(i, vec);
    }
    poly.setFillColor(sf::Color::Transparent);
    poly.setOutlineColor(b2ToSfColor(p_color));
    m_renderTarget.draw(poly);
}

void Box2dRenderer::DrawSolidPolygon(const b2Vec2* p_vertices,
                                     i32 p_vertexCount,
                                     const b2Color& p_color) {
    sf::ConvexShape poly(p_vertexCount);
    sf::Vector2f center;
    for (i32 i = 0; i < p_vertexCount; ++i) {
        sf::Vector2f vec = b2ToSfVector(p_vertices[i]);
        poly.setPoint(i, vec);
    }
    poly.setFillColor(b2ToSfColor(p_color, 60));
    poly.setOutlineColor(b2ToSfColor(p_color));
    m_renderTarget.draw(poly);
}

void Box2dRenderer::DrawCircle(const b2Vec2& p_center, f32 p_radius,
                               const b2Color& p_color) {
    sf::CircleShape circle(p_radius * SCALE);
    circle.setOrigin(p_radius * SCALE, p_radius * SCALE);
    circle.setPosition(b2ToSfVector(p_center));
    circle.setFillColor(sf::Color::Transparent);
    circle.setOutlineColor(b2ToSfColor(p_color));
    m_renderTarget.draw(circle);
}
void Box2dRenderer::DrawSolidCircle(const b2Vec2& p_center, f32 p_radius,
                                    const b2Vec2& p_axis,
                                    const b2Color& p_color) {
    sf::CircleShape circle(p_radius * SCALE);
    circle.setOrigin(p_radius * SCALE, p_radius * SCALE);
    circle.setPosition(b2ToSfVector(p_center));
    circle.setFillColor(sf::Color::Transparent);
    circle.setOutlineColor(b2ToSfColor(p_color));

    b2Vec2 endPoint = p_center + p_radius * p_axis;
    sf::Vertex line[2] = {
        sf::Vertex(b2ToSfVector(p_center), b2ToSfColor(p_color)),
        sf::Vertex(b2ToSfVector(endPoint), b2ToSfColor(p_color))};

    m_renderTarget.draw(circle);
    m_renderTarget.draw(line, 2, sf::Lines);
}

void Box2dRenderer::DrawSegment(const b2Vec2& p_p1, const b2Vec2& p_p2,
                                const b2Color& p_color) {
    sf::Vertex line[] = {sf::Vertex(b2ToSfVector(p_p1), b2ToSfColor(p_color)),
                         sf::Vertex(b2ToSfVector(p_p2), b2ToSfColor(p_color))};
    m_renderTarget.draw(line, 2, sf::Lines);
}

void Box2dRenderer::DrawTransform(const b2Transform& p_xf) {
    f32 length = 0.4f;
    b2Vec2 x = p_xf.p + length * p_xf.q.GetXAxis();
    sf::Vertex redLine[] = {sf::Vertex(b2ToSfVector(p_xf.p), sf::Color::Red),
                            sf::Vertex(b2ToSfVector(x), sf::Color::Red)};
    b2Vec2 y = p_xf.p + length * p_xf.q.GetYAxis();
    sf::Vertex greenLine[] = {
        sf::Vertex(b2ToSfVector(p_xf.p), sf::Color::Green),
        sf::Vertex(b2ToSfVector(y), sf::Color::Green)};
    m_renderTarget.draw(redLine, 2, sf::Lines);
    m_renderTarget.draw(greenLine, 2, sf::Lines);
}

void Box2dRenderer::DrawPoint(const b2Vec2& /*p_p*/, f32 /*p_size*/,
                              const b2Color& /*p_color*/) {}

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