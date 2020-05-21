#ifndef __DOODE_ENGINE_HPP__
#define __DOODE_ENGINE_HPP__

#include "Scene.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include <vector>

namespace doode {

class Engine {
public:
    Engine(std::shared_ptr<Scene> p_initial,
           std::map<std::string, std::shared_ptr<Scene>> p_scenes);
    void run();

private:
    sf::RenderWindow m_window;
    std::shared_ptr<Scene> m_activeScene;
    std::map<std::string, std::shared_ptr<Scene>> m_scenes;
};

} // namespace doode

#endif