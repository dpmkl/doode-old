#include "Engine.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/VideoMode.hpp"
#include "SFML/Window/WindowStyle.hpp"
#include "Scene.hpp"
#include "spdlog/spdlog.h"
#include <chrono>
#include <memory>

namespace stdt = std::chrono;

namespace doode {

Engine::Engine(std::shared_ptr<Scene> p_initial,
               std::map<std::string, std::shared_ptr<Scene>> p_scenes)
    : m_activeScene(p_initial), m_scenes(p_scenes) {}

void Engine::run() {
    m_window.create(sf::VideoMode(1280, 720), "doode", sf::Style::Titlebar);
    m_window.setFramerateLimit(60);
    m_window.setActive(true);
    const auto settings = m_window.getSettings();
    spdlog::info("OpenGl version: " + std::to_string(settings.majorVersion) +
                 "." + std::to_string(settings.minorVersion));

    m_activeScene->start(std::make_unique<SceneContext>());
    auto frameStart = stdt::high_resolution_clock::now();
    auto frameEnd = stdt::high_resolution_clock::now();
    while (m_window.isOpen()) {
        auto frameDelta =
            stdt::duration_cast<stdt::duration<f32>>(frameEnd - frameStart)
                .count();
        frameStart = std::chrono::high_resolution_clock::now();
        sf::Event event;
        while (m_window.pollEvent(event)) {
            if (!m_window.hasFocus()) {
                continue;
            }
            if (event.type == sf::Event::Closed) {
                m_window.close();
            }
            m_activeScene->events(event);
        }
        auto transition = m_activeScene->update(frameDelta);
        if (transition.has_value()) {
            auto data = std::move(transition.value());
            auto next = m_scenes.find(data.nextScene);
            if (next != m_scenes.end()) {
                m_activeScene = (*next).second;
                m_activeScene->start(std::move(data.context));
            } else {
                spdlog::error("Scene not found! '" + data.nextScene + "'");
            }
        }
        m_window.clear();
        m_activeScene->render(m_window);
        m_window.display();
        frameEnd = std::chrono::high_resolution_clock::now();
    }
}

} // namespace doode