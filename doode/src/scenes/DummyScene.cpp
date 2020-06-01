#include "DummyScene.hpp"
#include "../Types.hpp"
#include <chrono>
#include <memory>
#include <spdlog/spdlog.h>
#include <thread>

namespace doode {

void DummyScene::updateActive(const f32 /*p_delta*/) {
    spdlog::info("Dummy Active");
    changeScene("game", std::make_unique<SceneContext>());
}

void DummyScene::prepareProc(std::unique_ptr<SceneContext> /*p_context*/) {
    spdlog::info("Preparing dummy ...");
    setReady();
}

void DummyScene::cleanupProc() {
    spdlog::info("Cleaning up dummy ...");
    setClean();
}

} // namespace doode