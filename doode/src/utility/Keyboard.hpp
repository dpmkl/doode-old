#ifndef __DOODE_KEYBOARD_HPP__
#define __DOODE_KEYBOARD_HPP__

#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include <SFML/Main.hpp>
#include <unordered_map>
#include <array>

namespace doode {

class Keyboard {
public:
    Keyboard();

    void update(const sf::Event& p_event);
    void swap();

    auto isDown(sf::Keyboard::Key p_key) const -> bool;
    auto isUp(sf::Keyboard::Key p_key) const -> bool;

    auto isPressed(sf::Keyboard::Key p_key) const -> bool;
    auto isReleased(sf::Keyboard::Key p_key) const -> bool;

private:
    std::array<bool, sf::Keyboard::KeyCount> m_currKeys;
    std::array<bool, sf::Keyboard::KeyCount> m_prevKeys;
};

} // namespace doode

#endif