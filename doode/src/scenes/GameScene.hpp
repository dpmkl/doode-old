#ifndef __DOODE_GAMESCENE_HPP__
#define __DOODE_GAMESCENE_HPP__

#include "../Scene.hpp"
#include "../systems/SystemBase.hpp"
#include "../utility/Maze.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "box2d/b2_body.h"
#include <array>
#include <memory>

namespace doode {

class GameScene : public Scene {
public:
    GameScene() = default;
    ~GameScene() override = default;

protected:
    void addRenderSystem(std::unique_ptr<RenderSystemBase> p_system);
    void addUpdateSystem(std::unique_ptr<UpdateSystemBase> p_system);
    void addEventSystem(std::unique_ptr<EventSystemBase> p_system);

    void updateActive(f32 p_delta) override;
    void renderActive(sf::RenderTarget& p_renderTarget) override;
    void eventsActive(const sf::Event& p_event) override;

    void prepareProc(std::unique_ptr<SceneContext> p_context) override;
    void cleanupProc() override;

    virtual void setup();
    void setMaze(Maze p_maze);
    auto getMaze() const -> const Maze&;

private:
    Maze m_maze;
    std::vector<std::unique_ptr<RenderSystemBase>> m_renderSystems;
    std::vector<std::unique_ptr<UpdateSystemBase>> m_updateSystems;
    std::vector<std::unique_ptr<EventSystemBase>> m_eventSystems;
};

} // namespace doode

#endif