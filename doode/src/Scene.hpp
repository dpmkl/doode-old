#ifndef __DOODE_SCENE_HPP__
#define __DOODE_SCENE_HPP__

#include "Types.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>
#include <atomic>
#include <chrono>
#include <map>
#include <mutex>
#include <thread>
#include <variant>

namespace doode {

enum class SceneState {
    Hello,
    Preparing,
    Ready,
    Cleaning,
    Done,
};

struct SceneContext {
    std::map<std::string, std::variant<i32, u32, f32, bool, std::string>>
        params;
};

struct SceneTransition {
    std::string nextScene;
    std::unique_ptr<SceneContext> context;
};

class Scene {
public:
    Scene();
    virtual ~Scene();

    auto getState() -> SceneState;

    void start(std::unique_ptr<SceneContext> p_context);
    void events(const sf::Event& p_event);
    auto update(f32 p_delta) -> std::optional<SceneTransition>;
    void render(sf::RenderTarget& p_renderTarget);

protected:
    void changeScene(const std::string& p_name,
                     std::unique_ptr<SceneContext> p_context);

    virtual void eventsLoading(const sf::Event& /*p_event*/) {}
    virtual void eventsActive(const sf::Event& /*p_event*/) {}
    virtual void eventsUnloading(const sf::Event& /*p_event*/) {}

    virtual void updateLoading(f32 /*p_delta*/) {}
    virtual void updateActive(f32 /*p_delta*/) {}
    virtual void updateUnloading(f32 /*p_delta*/) {}

    virtual void renderLoading(sf::RenderTarget& /*p_renderTarget*/) {}
    virtual void renderActive(sf::RenderTarget& /*p_renderTarget*/) {}
    virtual void renderUnloading(sf::RenderTarget& /*p_renderTarget*/) {}

    virtual void prepareProc(std::unique_ptr<SceneContext> p_context);
    virtual void cleanupProc();

    void setReady();
    void setClean();

private:
    void setState(SceneState p_state);
    void prepare(std::unique_ptr<SceneContext> p_context);
    void cleanup();

    SceneState m_state;
    std::mutex m_stateMtx;
    std::optional<SceneTransition> m_transition;
};

} // namespace doode

#endif