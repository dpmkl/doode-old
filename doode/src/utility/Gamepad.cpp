#include "Gamepad.hpp"
#include <spdlog/spdlog.h>

namespace doode {

GamepadState::GamepadState() {
    for (auto i = 0; i < sf::Joystick::ButtonCount; ++i) {
        prevButtons[i] = false;
        currButtons[i] = false;
    }

    for (auto i = 0; i < sf::Joystick::AxisCount; ++i) {
        prevAxis[i] = 0;
        currAxis[i] = 0;
    }
}

auto Gamepad::isDown(const u8 p_pad, const u8 p_btn) const -> bool {
    if (m_states.count(p_pad) == 1) {
        return m_states.at(p_pad).currButtons[p_btn];
    } else {
        return false;
    }
}

auto Gamepad::isUp(const u8 p_pad, const u8 p_btn) const -> bool {
    if (m_states.count(p_pad) == 1) {
        return !m_states.at(p_pad).currButtons[p_btn];
    } else {
        return false;
    }
}

auto Gamepad::isPressed(const u8 p_pad, const u8 p_btn) const -> bool {
    if (m_states.count(p_pad) == 1) {
        return m_states.at(p_pad).currButtons[p_btn] &&
               !m_states.at(p_pad).prevButtons[p_btn];
    } else {
        return false;
    }
}

auto Gamepad::getAxis(const u8 p_pad, const u8 p_axis) const -> f32 {
    if (m_states.count(p_pad) == 1) {
        return m_states.at(p_pad).currAxis[p_axis];
    } else {
        return 0;
    }
}

void Gamepad::activate(const u8 p_gamepad) {
    if (m_states.count(p_gamepad) == 1) {
        m_states.emplace(p_gamepad, GamepadState());
    } else {
        spdlog::error("Gamepad '" + std::to_string(p_gamepad) + "' already activated!");        
    }
}

void Gamepad::deactivate(const u8 p_gamepad) {
    if (m_states.count(p_gamepad) == 0) {
        spdlog::error("Gamepad '" + std::to_string(p_gamepad) +
                      "' not activated!");
    } else {
        m_states.erase(p_gamepad);        
    }
}

void Gamepad::update() {
    for (auto& [id, state] : m_states) {
        if (sf::Joystick::isConnected(id)) {
            state.prevButtons = state.currButtons;
            for (auto i = 0; i < sf::Joystick::ButtonCount; ++i) {
                state.currButtons.at(i) = sf::Joystick::isButtonPressed(id, i);
            }
            for (auto i = 0; i < sf::Joystick::AxisCount; ++i) {
                state.currAxis.at(i) = sf::Joystick::getAxisPosition(
                    id, static_cast<sf::Joystick::Axis>(i));
            }
        }
    }
}

    
}