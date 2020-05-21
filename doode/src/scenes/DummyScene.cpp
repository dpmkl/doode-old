#include "DummyScene.hpp"
#include "../Types.hpp"
#include <chrono>
#include <memory>
#include <spdlog/spdlog.h>
#include <thread>

namespace doode {

void DummyScene::updateActive(const f32 p_delta) {
    spdlog::info("Dummy Active");
    changeScene("game", std::make_unique<SceneContext>());
}

void DummyScene::prepareProc(std::unique_ptr<SceneContext> p_context) {
    for (i32 i = 0; i < 3; ++i) {
        spdlog::info("Loading dummy ...");
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    setReady();
}

void DummyScene::cleanupProc() {
    for (i32 i = 0; i < 3; ++i) {
        spdlog::info("Cleaning up dummy ...");
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    setClean();
}

} // namespace doode