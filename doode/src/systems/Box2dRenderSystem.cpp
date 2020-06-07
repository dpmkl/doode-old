#include "Box2dRenderSystem.hpp"
#include "../Types.hpp"
#include "../utility/Physics.hpp"
#include "SFML/Config.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/ConvexShape.hpp"
#include "SFML/Graphics/PrimitiveType.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "box2d/b2_draw.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>
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

auto Box2dRenderer::isVisible(const b2Vec2* p_vertices, i32 p_vertexCount)
    -> bool {
    auto view = m_renderTarget.getView();
    auto center = view.getCenter();
    auto halfX = view.getSize().x * 0.5F;
    auto halfY = view.getSize().y * 0.5F;
    sf::FloatRect visible(center.x - halfX, center.y - halfY, halfX * 2,
                          halfY * 2);
    for (auto i = 0; i < p_vertexCount; ++i) {
        auto vertex = Physics::toSfml(p_vertices[i]);
        if (visible.contains(vertex)) {
            return true;
        }
    }
    return false;
}

void Box2dRenderer::DrawPolygon(const b2Vec2* p_vertices, i32 p_vertexCount,
                                const b2Color& p_color) {
    if (!isVisible(p_vertices, p_vertexCount)) {
        return;
    }
    sf::ConvexShape poly(p_vertexCount);
    sf::Vector2f center;
    for (i32 i = 0; i < p_vertexCount; ++i) {
        auto vert = p_vertices[i];
        sf::Vector2f vec = Physics::toSfml(vert);
        poly.setPoint(i, vec);
    }
    poly.setFillColor(sf::Color::Transparent);
    poly.setOutlineColor(b2ToSfColor(p_color));
    m_renderTarget.draw(poly);
}

void Box2dRenderer::DrawSolidPolygon(const b2Vec2* p_vertices,
                                     i32 p_vertexCount,
                                     const b2Color& p_color) {
    if (!isVisible(p_vertices, p_vertexCount)) {
        return;
    }
    sf::ConvexShape poly(p_vertexCount);
    sf::Vector2f center;
    for (i32 i = 0; i < p_vertexCount; ++i) {
        sf::Vector2f vec = Physics::toSfml(p_vertices[i]);
        poly.setPoint(i, vec);
    }
    poly.setFillColor(b2ToSfColor(p_color, 60));
    poly.setOutlineThickness(1);
    poly.setOutlineColor(sf::Color::White);
    m_renderTarget.draw(poly);
}

void Box2dRenderer::DrawCircle(const b2Vec2& p_center, f32 p_radius,
                               const b2Color& p_color) {
    sf::CircleShape circle(p_radius * SCALE);
    circle.setOrigin(p_radius * SCALE, p_radius * SCALE);
    circle.setPosition(Physics::toSfml(p_center));
    circle.setFillColor(sf::Color::Transparent);
    circle.setOutlineColor(b2ToSfColor(p_color));
    circle.setOutlineThickness(1.0F);
    m_renderTarget.draw(circle);
}
void Box2dRenderer::DrawSolidCircle(const b2Vec2& p_center, f32 p_radius,
                                    const b2Vec2& p_axis,
                                    const b2Color& p_color) {
    sf::CircleShape circle(p_radius * SCALE);
    circle.setOrigin(p_radius * SCALE, p_radius * SCALE);
    circle.setPosition(Physics::toSfml(p_center));
    circle.setFillColor(sf::Color::Transparent);
    circle.setOutlineColor(b2ToSfColor(p_color));
    circle.setOutlineThickness(1.0F);

    b2Vec2 endPoint = p_center + p_radius * p_axis;
    sf::Vertex line[2] = {
        sf::Vertex(Physics::toSfml(p_center), b2ToSfColor(p_color)),
        sf::Vertex(Physics::toSfml(endPoint), b2ToSfColor(p_color))};

    m_renderTarget.draw(circle);
    m_renderTarget.draw(line, 2, sf::Lines);
}

void Box2dRenderer::DrawSegment(const b2Vec2& p_p1, const b2Vec2& p_p2,
                                const b2Color& p_color) {
    sf::Vertex line[] = {
        sf::Vertex(Physics::toSfml(p_p1), b2ToSfColor(p_color)),
        sf::Vertex(Physics::toSfml(p_p2), b2ToSfColor(p_color))};
    m_renderTarget.draw(line, 2, sf::Lines);
}

void Box2dRenderer::DrawTransform(const b2Transform& p_xf) {
    f32 length = 0.4f;
    b2Vec2 x = p_xf.p + length * p_xf.q.GetXAxis();
    sf::Vertex redLine[] = {sf::Vertex(Physics::toSfml(p_xf.p), sf::Color::Red),
                            sf::Vertex(Physics::toSfml(x), sf::Color::Red)};
    b2Vec2 y = p_xf.p + length * p_xf.q.GetYAxis();
    sf::Vertex greenLine[] = {
        sf::Vertex(Physics::toSfml(p_xf.p), sf::Color::Green),
        sf::Vertex(Physics::toSfml(y), sf::Color::Green)};
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
        m_box2d->SetFlags(b2Draw::e_shapeBit | b2Draw::e_aabbBit);
        world.SetDebugDraw(m_box2d.get());
    }
    world.DebugDraw();
}

} // namespace doode