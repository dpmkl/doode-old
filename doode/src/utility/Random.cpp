#include "Random.hpp"

namespace doode {


void Random::init(u32 p_seed) { m_generator.seed(p_seed); }

auto Random::getNormal() -> f32 { 
	std::uniform_real_distribution<f32> dist(0, 1);
    return dist(m_generator);
}

auto Random::getInteger(i32 p_min, i32 p_max) -> i32 {
    std::uniform_int_distribution<i32> dist(p_min, p_max);
    return dist(m_generator);
}

}