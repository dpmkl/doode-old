#ifndef __DOODE_RANDOM_HPP__
#define __DOODE_RANDOM_HPP__

#include "../Types.hpp"
#include <random>
#include <memory>

namespace doode {

class Random {
public:
    void init(u32 p_seed);

    auto getNormal() -> f32;

    auto getInteger(i32 p_min, i32 p_max) -> i32;

private:
    std::mt19937 m_generator;    
};

}

#endif