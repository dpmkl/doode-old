#ifndef __DOODE_GAMESCENE_HPP__
#define __DOODE_GAMESCENE_HPP__

#include "../Scene.hpp"
#include "../systems/SystemBase.hpp"

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

private:
    std::vector<std::unique_ptr<RenderSystemBase>> m_renderSystems;
    std::vector<std::unique_ptr<UpdateSystemBase>> m_updateSystems;
};

} // namespace doode

#endif