#include "GameScene.hpp"
#include "../Physics.hpp"
#include "../Services.hpp"
#include "../Types.hpp"
#include "../systems/PhysicsSystem.hpp"
#include "box2d/b2_body.h"
#include "box2d/b2_polygon_shape.h"
#include <box2d/box2d.h>
#include <chrono>
#include <memory>
#include <spdlog/spdlog.h>
#include <thread>

namespace doode {

void GameScene::addRenderSystem(std::unique_ptr<RenderSystemBase> p_system) {
    m_renderSystems.emplace_back(std::move(p_system));
}
void GameScene::addUpdateSystem(std::unique_ptr<UpdateSystemBase> p_system) {
    m_updateSystems.emplace_back(std::move(p_system));
}

void GameScene::updateActive(const f32 p_delta) {
    for (auto& system : m_updateSystems) {
        system->update(p_delta, Services::Ecs::ref());
    }
}

void GameScene::renderActive(sf::RenderTarget& p_renderTarget) {
    for (auto& system : m_renderSystems) {
        system->render(p_renderTarget, Services::Ecs::ref());
    }
}

void GameScene::prepareProc(std::unique_ptr<SceneContext> /*p_context*/) {
    for (i32 i = 0; i < 3; ++i) {
        spdlog::info("Loading game ...");
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    Services::Ecs::set();
    Services::Physics::set(b2Vec2(0, -9.8f));

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

void GameScene::setup() { addUpdateSystem(std::make_unique<PhysicsSystem>()); }

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