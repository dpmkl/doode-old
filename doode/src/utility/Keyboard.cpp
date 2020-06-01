#include "Keyboard.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"

namespace doode {

Keyboard::Keyboard() {
    for (auto i = 0; i < sf::Keyboard::KeyCount; ++i) {
        auto key = static_cast<sf::Keyboard::Key>(i);
        m_currKeys[key] = false;
    }
}

void Keyboard::update(const sf::Event& p_event) {
    if (p_event.type == sf::Event::KeyPressed) {
        m_currKeys[p_event.key.code] = true;
    } else if (p_event.type == sf::Event::KeyReleased) {
        m_currKeys[p_event.key.code] = false;
    }
}

auto Keyboard::isDown(sf::Keyboard::Key p_key) const -> bool {
    return m_currKeys[p_key];
}
auto Keyboard::isUp(sf::Keyboard::Key p_key) const -> bool {
    return !m_currKeys[p_key];
}

auto Keyboard::isPressed(sf::Keyboard::Key p_key) const -> bool {
    return m_currKeys[p_key] && !m_prevKeys[p_key];
}
auto Keyboard::isReleased(sf::Keyboard::Key p_key) const -> bool {
    return !m_currKeys[p_key] && m_prevKeys[p_key];
}

void Keyboard::swap() { m_prevKeys = m_currKeys; }

} // namespace doode