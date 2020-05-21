#include "Scene.hpp"
#include <mutex>
#include <optional>
#include <spdlog/spdlog.h>

namespace doode {

Scene::Scene() : m_state(SceneState::Hello), m_transition(std::nullopt) {}

Scene::~Scene() {}

auto Scene::getState() -> SceneState {
    SceneState result;
    const std::lock_guard<std::mutex> lock(m_stateMtx);
    result = m_state;
    return result;
}

void Scene::start(std::unique_ptr<SceneContext> p_context) {
    m_transition = std::nullopt;
    prepare(std::move(p_context));
}

void Scene::events(const sf::Event& p_event) {
    switch (getState()) {
    case SceneState::Preparing:
        eventsLoading(p_event);
        break;
    case SceneState::Ready:
        eventsActive(p_event);
        break;
    case SceneState::Cleaning:
    case SceneState::Done:
        eventsUnloading(p_event);
        break;
    default:
        spdlog::error("Invalid scene state!");
        exit(1);
    }
}

auto Scene::update(const f32 p_delta) -> std::optional<SceneTransition> {
    switch (getState()) {
    case SceneState::Preparing:
        updateLoading(p_delta);
        return std::nullopt;
    case SceneState::Ready:
        updateActive(p_delta);
        return std::nullopt;
    case SceneState::Cleaning:
        updateUnloading(p_delta);
        return std::nullopt;
    case SceneState::Done:
        return std::move(m_transition);
    default:
        spdlog::error("Invalid scene state!");
        exit(1);
    }
}

void Scene::render(sf::RenderTarget& p_renderTarget) {
    switch (getState()) {
    case SceneState::Preparing:
        renderLoading(p_renderTarget);
        break;
    case SceneState::Ready:
        renderActive(p_renderTarget);
        break;
    case SceneState::Cleaning:
    case SceneState::Done:
        renderUnloading(p_renderTarget);
        break;
    default:
        spdlog::error("Invalid scene state!");
        exit(1);
    }
}

void Scene::changeScene(const std::string& p_name,
                        std::unique_ptr<SceneContext> p_loadContext) {
    m_transition = std::optional<SceneTransition>{
        SceneTransition{p_name, std::move(p_loadContext)}};
    cleanup();
}

void Scene::prepareProc(std::unique_ptr<SceneContext> /*p_context*/) {
    setReady();
}

void Scene::cleanupProc() { setClean(); }

void Scene::setReady() { setState(SceneState::Ready); }

void Scene::setClean() { setState(SceneState::Done); }

void Scene::setState(const SceneState p_state) {
    const std::lock_guard<std::mutex> lock(m_stateMtx);
    m_state = p_state;
}

void Scene::prepare(std::unique_ptr<SceneContext> p_context) {
    setState(SceneState::Preparing);
    std::thread thread(&Scene::prepareProc, this, std::move(p_context));
    thread.detach();
}

void Scene::cleanup() {
    setState(SceneState::Cleaning);
    std::thread thread(&Scene::cleanupProc, this);
    thread.detach();
}

} // namespace doode