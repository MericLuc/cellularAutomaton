#include "random.h"
#include <ctime>

/*!
 * \file random.cpp
 * \brief Implementations of the functions defined in \a random.h
 * \author lhm
 */

Random& Random::get()
{
    static Random r;
    return r;
}

Random::Random()
{
    m_rng.seed ((unsigned)std::time(nullptr));
}

int Random::rand_int(const int p_min, const int p_max)
{
    std::uniform_int_distribution<int> dist(p_min, p_max);
    return dist(m_rng);
}

float Random::rand_float(const float& p_min, const float& p_max)
{
    std::uniform_real_distribution<float> dist(p_min, p_max);
    return dist(m_rng);
}
