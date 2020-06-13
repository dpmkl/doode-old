#ifndef __DOODE_GAMEPAD_HPP__
#define __DOODE_GAMEPAD_HPP__

#include "../Types.hpp"
#include <SFML/Window/Joystick.hpp>
#include <array>
#include <map>

namespace doode {

struct GamepadState {
    GamepadState();
    std::array<f32, sf::Joystick::AxisCount> prevAxis;
    std::array<f32, sf::Joystick::AxisCount> currAxis;
    std::array<bool, sf::Joystick::ButtonCount> prevButtons;
    std::array<bool, sf::Joystick::ButtonCount> currButtons;
};

class Gamepad {
public:
    auto isDown(u8 p_pad, u8 p_btn) const -> bool;
    auto isUp(u8 p_pad, u8 p_btn) const -> bool;
    auto isPressed(u8 p_pad, u8 p_btn) const -> bool;    
    auto getAxis(u8 p_pad, u8 p_axis) const -> f32;

    void activate(u8 p_gamepad);
    void deactivate(u8 p_gamepad);

    void update();

private:
    std::map<u8, GamepadState> m_states;
};

}

#endif