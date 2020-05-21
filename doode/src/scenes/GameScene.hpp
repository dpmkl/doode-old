#ifndef __DOODE_GAMESCENE_HPP__
#define __DOODE_GAMESCENE_HPP__

#include "../Scene.hpp"

namespace doode {

class GameScene : public Scene {
public:
    GameScene() = default;
    ~GameScene() override = default;

protected:
    void updateActive(f32 p_delta) override;

    void prepareProc(std::unique_ptr<SceneContext> p_context) override;
    void cleanupProc() override;
};

} // namespace doode

#endif