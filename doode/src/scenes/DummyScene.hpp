#ifndef __DOODE_DUMMYSCENE_HPP__
#define __DOODE_DUMMYSCENE_HPP__

#include "../Scene.hpp"

namespace doode {

class DummyScene : public Scene {
protected:
    void updateActive(f32 p_delta) override;

    void prepareProc(std::unique_ptr<SceneContext> p_context) override;
    void cleanupProc() override;
};

} // namespace doode

#endif