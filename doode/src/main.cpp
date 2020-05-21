#include "Engine.hpp"
#include "Types.hpp"
#include "scenes/DummyScene.hpp"
#include "scenes/GameScene.hpp"
#include "spdlog/common.h"
#include <entt/entt.hpp>
#include <memory>
#include <spdlog/spdlog.h>

auto main(i32 argc, char** argv) -> i32 {
    spdlog::set_pattern("%t %+");
    auto dummy = std::make_shared<doode::DummyScene>();
    auto game = std::make_shared<doode::GameScene>();
    doode::Engine engine(dummy, {{"dummy", dummy}, {"game", game}});
    engine.run();
    return 0;
}
