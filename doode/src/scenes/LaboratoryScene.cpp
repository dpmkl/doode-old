#include "LaboratoryScene.hpp"
#include "../systems/Box2dRenderSystem.hpp"
#include "../utility/GameFactory.hpp"
#include "GameScene.hpp"
#include "SFML/System/Vector2.hpp"
#include "box2d/b2_world.h"
#include <memory>

namespace doode {

void LaboratoryScene::setup() {
    GameScene::setup();
    addRenderSystem(std::make_unique<Box2dRenderSystem>());

    createMaze(17, 0xcafeaffe);

    auto& ecs = Services::Ecs::ref();
    auto& world = Services::Physics::ref();

    GameFactory::createPlayer(ecs, world);
}

} // namespace doode