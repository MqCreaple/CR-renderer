#pragma once

#include <glm/glm.hpp>
#include <ctime>

class Random {
    // TODO (rewrite the random class)
public:
    /**
     * @brief random integer in range [iMin, iMax)
     * @param iMin lower bound (inclusive)
     * @param iMax upper bound (exclusive)
     * @return int random integer in the range
     */
    static int randInt(int iMin, int iMax);

    /**
     * @brief select an object randomly from a list with given weight to each choice.
     * @tparam T type of object
     * @param n number of objects
     * @param vals objects
     * @param weights weights to each object
     * @return T randomly selected object
     */
    template<typename T>
    static T randSelect(size_t n, const T* vals, float* weights, int& index);
    
    /**
     * @brief generate uniform random number in [0, 1)
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
};

template<typename T>
T Random::randSelect(size_t n, const T* objects, float* weights, int& index) {
    float acc[n];
    acc[0] = weights[0];
    for(int i = 1; i < n; i++) {
        acc[i] = acc[i-1] + weights[i];
    }
    float maxF = acc[n-1];
    float randn = uniform(0, maxF);

    int left = -1, right = n;
    while(left < right - 1) {
        int mid = (left + right) / 2;
        if(acc[mid] > randn) {
            right = mid;
        } else {
            left = mid;
        }
    }
    index = right;
    return objects[right];
}