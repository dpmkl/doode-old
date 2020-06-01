#ifndef __DOODE_MAZE_HPP__
#define __DOODE_MAZE_HPP__

#include "../Types.hpp"
#include "SFML/Graphics/Image.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

namespace doode {

class Maze {
public:
    static constexpr u8 NORTH = 0x1;
    static constexpr u8 SOUTH = 0x2;
    static constexpr u8 WEST = 0x4;
    static constexpr u8 EAST = 0x8;
    static constexpr u8 ALL = 0xF;

    Maze();

    void init(u32 p_width, u32 p_height);

    auto at(u32 p_x, u32 p_y) const -> u8;

    auto has(u32 p_x, u32 p_y, u8 p_direction) const -> bool;

    void generate(u32 p_seed, f32 p_bias = 0.5F);

    auto render() const -> sf::Image;

private:
    void unset(u32 p_x, u32 p_y, u8 p_cell);
    u32 m_width;
    u32 m_height;
    std::vector<u8> m_cells;
};

} // namespace doode

#endif