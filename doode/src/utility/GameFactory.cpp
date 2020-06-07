#include "GameFactory.hpp"
#include "../Types.hpp"
#include "../components/CharacterControlComponent.hpp"
#include "../components/PhysicsComponent.hpp"
#include "../components/Tags.hpp"
#include "Maze.hpp"
#include "Physics.hpp"
#include "SFML/System/Vector2.hpp"
#include "box2d/b2_body.h"
#include "box2d/b2_world.h"
#include <memory>
#include <spdlog/spdlog.h>

namespace doode {

constexpr f32 WALL_WIDTH = 400.0F;
constexpr f32 WALL_HEIGHT = WALL_WIDTH / 48.0F;

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
    static CollisionInfo torsoCollisionInfo{CollisionType::Body, p_entity,
                                            "character"};
    b2PolygonShape poly;
    poly.SetAsBox(size.x, size.y / 2);
    b2FixtureDef fixture;
    fixture.shape = &poly;
    fixture.density = 1;
    fixture.userData = &torsoCollisionInfo;
    body->CreateFixture(&fixture);

    // Wheel
    static CollisionInfo wheelCollisionInfo{CollisionType::Feet, p_entity,
                                            "character"};
    b2CircleShape wheel;
    wheel.m_radius = size.x * 0.8F;
    wheel.m_p.Set(0, size.y * 0.40F);
    fixture.shape = &wheel;
    fixture.userData = &wheelCollisionInfo;
    body->CreateFixture(&fixture);

    // Sensor left
    static CollisionInfo leftSensorCollisionInfo{CollisionType::SensorLeft,
                                                 p_entity, "character"};
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
    static CollisionInfo rightSensorCollisionInfo{CollisionType::SensorRight,
                                                  p_entity, "character"};
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

void GameFactory::createStaticBlock(const sf::Vector2f& p_position,
                                    const sf::Vector2f& p_size,
                                    b2World& p_world) {
    auto size = Physics::toBox2d(p_size / 2.0f);
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position = Physics::toBox2d(p_position);
    b2PolygonShape bodyShape;
    bodyShape.SetAsBox(size.x, size.y);
    auto body = p_world.CreateBody(&bodyDef);
    body->CreateFixture(&bodyShape, 0.0f);
}

void GameFactory::createPlatform(entt::registry& p_ecs, b2World& p_world,
                                 const sf::Vector2f& p_position,
                                 const f32 p_range) {
    auto entity = p_ecs.create();
    auto dim = sf::Vector2f(WALL_WIDTH / 8, WALL_HEIGHT / 2);
    auto size = Physics::toBox2d(dim / 2.0f);
    b2BodyDef bodyDef;
    bodyDef.type = b2_kinematicBody;
    bodyDef.position = Physics::toBox2d(p_position);
    b2PolygonShape bodyShape;
    bodyShape.SetAsBox(size.x, size.y);
    auto body = p_world.CreateBody(&bodyDef);
    body->CreateFixture(&bodyShape, 0.0f);
    p_ecs.emplace<PhysicsComponent>(entity, body);
    if (p_range != 0) {
    }
}

auto GameFactory::createMaze(u32 p_size, u32 p_seed, b2World& p_world) -> Maze {
    if ((p_size % 2) != 1) {
        spdlog::error("Invalid maze size, must be uneven!");
        exit(1);
    }
    spdlog::info("Creating maze of size " + std::to_string(p_size) +
                 " and seed " + std::to_string(p_seed));

    Maze maze;
    maze.init(p_size, p_size);
    maze.generate(p_seed, 0.85F);

    const f32 half = WALL_WIDTH * 0.5F;
    const f32 size = p_size * WALL_WIDTH;
    f32 x = (p_size * WALL_WIDTH) * -0.5F;
    f32 y = (p_size * WALL_WIDTH) * -0.5F;
    usize count = 0;
    for (u32 row = 0; row < p_size; ++row) {
        for (u32 col = 0; col < p_size; ++col) {
            const auto xOffset = col * WALL_WIDTH;
            const auto yOffset = row * WALL_WIDTH;
            const auto center =
                sf::Vector2f(x + xOffset + half, y + yOffset + half);
            // createStaticBlock(center, sf::Vector2f(WALL_HEIGHT, WALL_HEIGHT),
            //                   p_world);

            // north
            if (row != 0 && maze.has(col, row, Maze::NORTH) &&
                !maze.has(col, row - 1, Maze::SOUTH)) {
                createStaticBlock(center + sf::Vector2f(0, -half),
                                  sf::Vector2f(WALL_WIDTH, WALL_HEIGHT),
                                  p_world);
                ++count;
            }

            // south
            if (row != p_size - 1 && maze.has(col, row, Maze::SOUTH)) {
                createStaticBlock(center + sf::Vector2f(0, half),
                                  sf::Vector2f(WALL_WIDTH, WALL_HEIGHT),
                                  p_world);
                ++count;
            }

            // west
            if (col != 0 && maze.has(col, row, Maze::WEST) &&
                !maze.has(col - 1, row, Maze::EAST)) {
                createStaticBlock(center + sf::Vector2f(-half, 0),
                                  sf::Vector2f(WALL_HEIGHT, WALL_WIDTH),
                                  p_world);
                ++count;
            }

            // east
            if (col != p_size - 1 && maze.has(col, row, Maze::EAST)) {
                createStaticBlock(center + sf::Vector2f(half, 0),
                                  sf::Vector2f(WALL_HEIGHT, WALL_WIDTH),
                                  p_world);
                ++count;
            }
        }
    }

    spdlog::info("Created " + std::to_string(count) + " platforms");

    createStaticBlock(sf::Vector2f(0, size * -0.5F),
                      sf::Vector2f(size + (1 * WALL_HEIGHT), WALL_HEIGHT),
                      p_world);

    createStaticBlock(sf::Vector2f(0, size * 0.5F),
                      sf::Vector2f(size + (1 * WALL_HEIGHT), WALL_HEIGHT),
                      p_world);

    createStaticBlock(sf::Vector2f(size * -0.5F, 0),
                      sf::Vector2f(WALL_HEIGHT, size + (1 * WALL_HEIGHT)),
                      p_world);

    createStaticBlock(sf::Vector2f(size * 0.5F, 0),
                      sf::Vector2f(WALL_HEIGHT, size + (1 * WALL_HEIGHT)),
                      p_world);
    return maze;
}

} // namespace doode