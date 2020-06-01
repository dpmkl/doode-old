#ifndef __DOODE_GAMESCENE_HPP__
#define __DOODE_GAMESCENE_HPP__

#include "../Scene.hpp"
#include "../systems/SystemBase.hpp"
#include "../utility/Maze.hpp"
#include "SFML/System/Vector2.hpp"
#include <memory>

namespace doode {

class GameScene : public Scene {
public:
    GameScene() = default;
    ~GameScene() override = default;

protected:
    void addRenderSystem(std::unique_ptr<RenderSystemBase> p_system);
    void addUpdateSystem(std::unique_ptr<UpdateSystemBase> p_system);

    void updateActive(f32 p_delta) override;
    void renderActive(sf::RenderTarget& p_renderTarget) override;

    void prepareProc(std::unique_ptr<SceneContext> p_context) override;
    void cleanupProc() override;

    virtual void setup();

    void createMaze(u32 p_size, u32 p_seed);
    auto getMaze() const -> const Maze&;
    void createStaticBlock(const sf::Vector2f& p_position,
                           const sf::Vector2f& p_size);

    static constexpr f32 WALL_WIDTH = 24.0F;
    static constexpr f32 WALL_HEIGHT = WALL_WIDTH / 48.0F;

private:
    Maze m_maze;
    std::vector<std::unique_ptr<RenderSystemBase>> m_renderSystems;
    std::vector<std::unique_ptr<UpdateSystemBase>> m_updateSystems;
};

} // namespace doode

#endif