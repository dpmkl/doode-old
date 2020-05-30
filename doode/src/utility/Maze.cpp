#include "Maze.hpp"
#include <random>

namespace doode {

Maze::Maze(u32 p_width, u32 p_height)
    : m_width(p_width), m_height(p_height), m_cells(p_width * p_height) {
    for (u32 i = 0; i < p_width * p_height; ++i) {
        m_cells[i] = ALL;
    }
}

auto Maze::at(u32 p_x, u32 p_y) const -> u8 {
    return m_cells[p_y * m_width + p_x];
}

void Maze::generate(u32 p_seed, f32 p_bias) {
    std::mt19937 rand(p_seed);
    std::uniform_real_distribution<f32> dis(0.0, 1.0);

    std::vector<u32> l(m_width);
    std::vector<u32> r(m_width);

    for (u32 cell = 0; cell < m_width; ++cell) {
        l[cell] = cell;
        r[cell] = cell;
    }

    for (u32 row = 0; row < m_height - 1; ++row) {
        for (u32 col = 0; col < m_width; ++col) {
            if (col != m_width - 1 && col + 1 != r[col] && dis(rand) < p_bias) {
                r[l[col + 1]] = r[col];
                l[r[col]] = l[col + 1];
                r[col] = col + 1;
                l[col + 1] = col;
                unset(col, row, EAST);
                unset(col + 1, row, WEST);
            }
            if (col != r[col] && dis(rand) < p_bias) {
                r[l[col]] = r[col];
                l[r[col]] = l[col];
                r[col] = col;
                l[col] = col;
            } else {
                unset(col, row, SOUTH);
                unset(col, row + 1, NORTH);
            }
        }
    }
    for (u32 col = 0; col < m_width; ++col) {
        if (col != m_width - 1 && col + 1 != r[col] &&
            (col = r[col] || dis(rand) < p_bias)) {
            r[l[col + 1]] = r[col];
            l[r[col]] = l[col + 1];
            r[col] = col + 1;
            l[col + 1] = col;
            unset(col, m_height - 1, EAST);
            unset(col + 1, m_height - 1, WEST);
        }

        r[l[col]] = r[col];
        l[r[col]] = l[col];
        r[col] = col;
        l[col] = col;
    }
}

void Maze::unset(u32 p_x, u32 p_y, u8 p_cell) {
    m_cells[p_y * m_width + p_x] = at(p_x, p_y) & ~static_cast<u8>(p_cell);
}

} // namespace doode