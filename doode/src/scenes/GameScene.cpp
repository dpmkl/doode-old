#include "GameScene.hpp"
#include "../Services.hpp"
#include "../Types.hpp"
#include "../components/CharacterControlComponent.hpp"
#include "../components/Tags.hpp"
#include "../systems/CameraFollowSystem.hpp"
#include "../systems/CharacterControlSystem.hpp"
#include "../systems/PhysicsSystem.hpp"
#include "../utility/ContactListener.hpp"
#include "../utility/GameFactory.hpp"
#include "../utility/Physics.hpp"
#include "SFML/System/Vector2.hpp"
#include "box2d/b2_body.h"
#include "box2d/b2_polygon_shape.h"
#include <box2d/box2d.h>
#include <chrono>
#include <memory>
#include <spdlog/spdlog.h>
#include <string>
#include <thread>

namespace doode {

void GameScene::addRenderSystem(std::unique_ptr<RenderSystemBase> p_system) {
    m_renderSystems.emplace_back(std::move(p_system));
}

void GameScene::addUpdateSystem(std::unique_ptr<UpdateSystemBase> p_system) {
    m_updateSystems.emplace_back(std::move(p_system));
}

void GameScene::addEventSystem(std::unique_ptr<EventSystemBase> p_system) {
    m_eventSystems.emplace_back(std::move(p_system));
}

void GameScene::updateActive(const f32 p_delta) {
    auto& ecs = Services::Ecs::ref();
    for (auto& system : m_updateSystems) {
        system->update(p_delta, ecs);
    }
    Services::Keyboard::ref().swap();
}

void GameScene::renderActive(sf::RenderTarget& p_renderTarget) {
    auto& ecs = Services::Ecs::ref();
    for (auto& system : m_renderSystems) {
        system->render(p_renderTarget, ecs);
    }
}

void GameScene::eventsActive(const sf::Event& p_event) {
    auto& ecs = Services::Ecs::ref();
    for (auto& system : m_eventSystems) {
        system->event(p_event, ecs);
    }
    Services::Keyboard::ref().update(p_event);
}

void GameScene::prepareProc(std::unique_ptr<SceneContext> /*p_context*/) {
    Services::Ecs::set();
    static ContactListener s_contactListener(Services::Ecs::ref());
    Services::Physics::set(b2Vec2(0, 9.8f));
    Services::Physics::ref().SetContactListener(&s_contactListener);
    Services::Keyboard::set();

    setup();
    setReady();
}

void GameScene::cleanupProc() {
    for (i32 i = 0; i < 3; ++i) {
        spdlog::info("Cleaning up game ...");
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    setClean();
}

void GameScene::setup() {
    addUpdateSystem(std::make_unique<PhysicsSystem>());
    addUpdateSystem(std::make_unique<CharacterControlSystem>());

    addRenderSystem(std::make_unique<CameraFollowSystem>());
}

void GameScene::createMaze(u32 p_size, u32 p_seed) {
    if ((p_size % 2) != 1) {
        spdlog::error("Invalid maze size, must be uneven!");
        exit(1);
    }
    spdlog::info("Creating maze of size " + std::to_string(p_size) +
                 " and seed " + std::to_string(p_seed));

    m_maze.init(p_size, p_size);
    m_maze.generate(p_seed, 0.85F);

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
            createStaticBlock(center, sf::Vector2f(WALL_HEIGHT, WALL_HEIGHT));

            // north
            if (row != 0 && m_maze.has(col, row, Maze::NORTH) &&
                !m_maze.has(col, row - 1, Maze::SOUTH)) {
                createStaticBlock(center + sf::Vector2f(0, -half),
                                  sf::Vector2f(WALL_WIDTH, WALL_HEIGHT));
                ++count;
            }

            // south
            if (row != p_size - 1 && m_maze.has(col, row, Maze::SOUTH)) {
                createStaticBlock(center + sf::Vector2f(0, half),
                                  sf::Vector2f(WALL_WIDTH, WALL_HEIGHT));
                ++count;
            }

            // west
            if (col != 0 && m_maze.has(col, row, Maze::WEST) &&
                !m_maze.has(col - 1, row, Maze::EAST)) {
                createStaticBlock(center + sf::Vector2f(-half, 0),
                                  sf::Vector2f(WALL_HEIGHT, WALL_WIDTH));
                ++count;
            }

            // east
            if (col != p_size - 1 && m_maze.has(col, row, Maze::EAST)) {
                createStaticBlock(center + sf::Vector2f(half, 0),
                                  sf::Vector2f(WALL_HEIGHT, WALL_WIDTH));
                ++count;
            }
        }
    }

    spdlog::info("Created " + std::to_string(count) + " platforms");

    createStaticBlock(sf::Vector2f(0, size * -0.5F),
                      sf::Vector2f(size + (1 * WALL_HEIGHT), WALL_HEIGHT));

    createStaticBlock(sf::Vector2f(0, size * 0.5F),
                      sf::Vector2f(size + (1 * WALL_HEIGHT), WALL_HEIGHT));

    createStaticBlock(sf::Vector2f(size * -0.5F, 0),
                      sf::Vector2f(WALL_HEIGHT, size + (1 * WALL_HEIGHT)));

    createStaticBlock(sf::Vector2f(size * 0.5F, 0),
                      sf::Vector2f(WALL_HEIGHT, size + (1 * WALL_HEIGHT)));
} // namespace doode

auto GameScene::getMaze() const -> const Maze& { return m_maze; }

void GameScene::createStaticBlock(const sf::Vector2f& p_position,
                                  const sf::Vector2f& p_size) {
    auto size = Physics::toBox2d(p_size / 2.0f);
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position = Physics::toBox2d(p_position);
    b2PolygonShape bodyShape;
    bodyShape.SetAsBox(size.x, size.y);
    auto body = Services::Physics::ref().CreateBody(&bodyDef);
    body->CreateFixture(&bodyShape, 0.0f);
}

} // namespace doode