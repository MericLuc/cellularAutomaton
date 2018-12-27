#ifndef RANDOM_H
#define RANDOM_H

#include <random>

/*!
 * \file random.h
 * \brief Random numbers generation used by random operations in the simulation
 * \author lhm
 */

/*!
 * \class Random
 * \brief Random numbers generation.
 * <ul>
 * <li> Generate with \a get method
 * <li> Produce a random int with \a rand_int method
 * <li> Produce a random float with \a rand_float method
 * </ul>
 */
class Random
{
    public:
        /*!
         * Factory method
         */
        static Random& get();

        /*!
         * Copy constructor is prohibited.
         */
        Random              (const Random& other)    = delete;

        /*!
         * Assignment constructor is prohibited.
         */
        Random& operator=   (const Random& other)   = delete;

        /*!
         * \function rand_int
         * \brief Returns an integer in the specified range of values.
         * \param p_min minimal value allowed.
         * \param p_max maximal value allowed.
         */
        int rand_int(const int p_min, const int p_max);

        /*!
         * \function rand_float
         * \brief Returns a floating value in the specified range of values.
         * \param p_min minimal value allowed.
         * \param p_max maximal value allowed.
         */
        float rand_float(const float& p_min, const float& p_max);

    private:
        Random();

        /*!
         * Random number generation based on <em> Mersenne Twister </em> algorithm.
         */
        std::mt19937 m_rng;
};

#endif // RANDOM_H
