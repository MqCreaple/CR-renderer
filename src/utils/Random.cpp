#include "utils/Random.h"

int Random::randInt(int iMin, int iMax) {
    return rand() % (iMax - iMin) + iMin;
}

float Random::uniform() {
    return rand() / (RAND_MAX * 1.0f);
}

float Random::uniform(float fmin, float fmax) {
    return uniform() * (fmax - fmin) + fmin;
}

glm::vec3 Random::unitVec() {
    float z = uniform() * 2 - 1;
    float phi = 2 * M_PI * uniform();
    float t = sqrt(1 - z * z);
    return glm::vec3(t * cos(phi), t * sin(phi), z);
}

glm::vec3 Random::vecOnHemisphere() {
    float z = uniform();
    float phi = 2 * M_PI * uniform();
    float t = sqrt(1 - z * z);
    return glm::vec3(t * cos(phi), t * sin(phi), z);
}