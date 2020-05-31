#include "LaboratoryScene.hpp"
#include "../systems/Box2dRenderSystem.hpp"
#include "GameScene.hpp"
#include "SFML/System/Vector2.hpp"
#include <memory>

namespace doode {

void LaboratoryScene::setup() {
    GameScene::setup();
    addRenderSystem(std::make_unique<Box2dRenderSystem>());

    createStaticBlock(sf::Vector2f(200, 200), sf::Vector2f(100, 100));
}

} // namespace doode