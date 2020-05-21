#include "GameScene.hpp"
#include "../Types.hpp"
#include <chrono>
#include <memory>
#include <spdlog/spdlog.h>
#include <thread>

namespace doode {

void GameScene::updateActive(const f32 p_delta) { spdlog::info("Game Active"); }

void GameScene::prepareProc(std::unique_ptr<SceneContext> p_context) {
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