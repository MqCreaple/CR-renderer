#pragma once

#include <glm/glm.hpp>
#include <ctime>

class Random {
public:
    /**
     * @brief generate uniform random number in [0, 1]
     * @return float random number
     */
    static float uniform();

    /**
     * @brief generate uniform random number in [fmin, fmax]
     * @param fmin lower bound
     * @param fmax upper bound
     * @return float random number
     */
    static float uniform(float fmin, float fmax);

    /**
     * @brief generate a random unit vector uniformly distributed on the unit sphere.
     * @return glm::vec3 random unit vector
     */
    static glm::vec3 unitVec();

    /**
     * @brief pick a random unit vector on the hemisphere (z >= 0).
     * @return glm::vec3 random unit vector
     */
    static glm::vec3 vecOnHemisphere();
private:
    static uint32_t rnd;
    /**
     * @brief update random number
     */
    static void updRnd();
};