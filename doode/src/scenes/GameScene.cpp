#include "GameScene.hpp"
#include "../Types.hpp"
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
    spdlog::info("Game Active");
    for (auto& system : m_updateSystems) {
        system->update(m_ecs, p_delta);
    }
}

void GameScene::renderActive(sf::RenderTarget& p_renderTarget) {
    for (auto& system : m_renderSystems) {
        system->render(p_renderTarget);
    }
}

void GameScene::prepareProc(std::unique_ptr<SceneContext> /*p_context*/) {
    for (i32 i = 0; i < 3; ++i) {
        spdlog::info("Loading game ...");
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    setReady();
}

void GameScene::cleanupProc() {
    for (i32 i = 0; i < 3; ++i) {
        spdlog::info("Cleaning up game ...");
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    setClean();
}

} // namespace doode