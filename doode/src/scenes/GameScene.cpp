#include "GameScene.hpp"
#include "../Services.hpp"
#include "../Types.hpp"
#include "../components/CharacterControlComponent.hpp"
#include "../components/Tags.hpp"
#include "../systems/CameraFollowSystem.hpp"
#include "../systems/CharacterControlSystem.hpp"
#include "../systems/MovingPlatformSystem.hpp"
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
    addUpdateSystem(std::make_unique<MovingPlatformSystem>());

    addRenderSystem(std::make_unique<CameraFollowSystem>());
}

void GameScene::setMaze(Maze p_maze) { m_maze = p_maze; }

auto GameScene::getMaze() const -> const Maze& { return m_maze; }

} // namespace doode