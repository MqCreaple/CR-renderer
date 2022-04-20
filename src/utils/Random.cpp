#include "utils/Random.h"

uint32_t Random::rnd = 0x4b1293c8U;

float Random::uniform() {
    updRnd();
    return rnd * 1.0f / UINT32_MAX;
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

void Random::updRnd() {
    rnd ^= rnd << 15;
    rnd += 0x1b4043d1;
    rnd ^= rnd >> 12;
    rnd ^= (uint32_t) time(NULL);
}