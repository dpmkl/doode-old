#include "LaboratoryScene.hpp"
#include "../systems/Box2dRenderSystem.hpp"
#include "GameScene.hpp"
#include "SFML/System/Vector2.hpp"
#include <memory>

namespace doode {

void LaboratoryScene::setup() {
    GameScene::setup();
    addRenderSystem(std::make_unique<Box2dRenderSystem>());

    createMaze(17, 0xcafeaffe);

    createPlayer();
}

} // namespace doode