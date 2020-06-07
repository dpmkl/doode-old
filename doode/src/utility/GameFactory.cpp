#include "GameFactory.hpp"
#include "../Types.hpp"
#include "../components/CharacterControlComponent.hpp"
#include "../components/PhysicsComponent.hpp"
#include "../components/Tags.hpp"
#include "Physics.hpp"
#include <memory>

namespace doode {

auto GameFactory::createCharacter(entt::entity p_entity, b2World& p_world)
    -> b2Body* {
    const f32 charHeight = 48;
    const f32 charWidth = 12;
    const auto size = Physics::toBox2d(sf::Vector2f(charWidth, charHeight));
    b2BodyDef def;
    def.type = b2BodyType::b2_dynamicBody;
    def.fixedRotation = true;
    def.position = b2Vec2(0, 0);
    def.angle = 0;
    def.bullet = true;
    auto body = p_world.CreateBody(&def);

    // Torso
    static CollisionInfo torsoCollisionInfo{.type = CollisionType::Body,
                                            .entity = p_entity};
    b2PolygonShape poly;
    poly.SetAsBox(size.x, size.y / 2);
    b2FixtureDef fixture;
    fixture.shape = &poly;
    fixture.density = 1;
    fixture.userData = &torsoCollisionInfo;
    body->CreateFixture(&fixture);

    // Wheel
    static CollisionInfo wheelCollisionInfo{.type = CollisionType::Feet,
                                            .entity = p_entity};
    b2CircleShape wheel;
    wheel.m_radius = size.x * 0.8F;
    wheel.m_p.Set(0, size.y * 0.40F);
    fixture.shape = &wheel;
    fixture.userData = &wheelCollisionInfo;
    body->CreateFixture(&fixture);

    // Sensor left
    static CollisionInfo leftSensorCollisionInfo{
        .type = CollisionType::SensorLeft, .entity = p_entity};
    fixture.userData = &leftSensorCollisionInfo;
    fixture.isSensor = true;
    fixture.density = 0;
    wheel.m_radius = size.y / 3;
    auto x = size.x;
    wheel.m_p.Set(-x + (x / 2), size.y / -4);
    body->CreateFixture(&fixture);
    wheel.m_p.Set(-x + (x / 2), size.y / 4);
    body->CreateFixture(&fixture);

    // Sensor right
    static CollisionInfo rightSensorCollisionInfo{
        .type = CollisionType::SensorRight, .entity = p_entity};
    fixture.userData = &rightSensorCollisionInfo;
    wheel.m_p.Set(x - (x / 2), size.y / -4);
    body->CreateFixture(&fixture);
    wheel.m_p.Set(x - (x / 2), size.y / 4);
    body->CreateFixture(&fixture);
    return body;
}

void GameFactory::createPlayer(entt::registry& p_ecs, b2World& p_world) {
    auto entity = p_ecs.create();
    auto character = createCharacter(entity, p_world);
    p_ecs.emplace<CharacterControlComponent>(entity, character);
    p_ecs.emplace<CameraFollow>(entity);
}

} // namespace doode