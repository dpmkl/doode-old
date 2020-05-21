#ifndef __DOODE_GAMESCENE_HPP__
#define __DOODE_GAMESCENE_HPP__

#include "../Scene.hpp"

namespace doode {

class GameScene : public Scene {
protected:
    void updateActive(f32 p_delta) override;

    void prepareProc(std::unique_ptr<SceneContext> p_context) override;
    void cleanupProc() override;
};

} // namespace doode

#endif