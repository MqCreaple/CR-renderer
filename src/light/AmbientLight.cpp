#include "light/AmbientLight.h"

AmbientLight::AmbientLight(size_t width, size_t height): SphericalTextureMap(width, height), sum(0) {}

void AmbientLight::set(int i, int j, Spectrum val) {
    SphericalTextureMap::set(i, j, val);
    this->sum += val;   // TODO (incorrect sum)
}

Spectrum AmbientLight::getSum() const {
    return sum;
}

Spectrum AmbientLight::map(const glm::vec3& local) const {
    float phi = atan(local.y / local.x);
    if(local.x < 0) {
        phi += M_PI;
    }
    if(phi < 0) {
        phi += 2 * M_PI;
    }
    float theta = acos(local.z);
    float u = phi * (this->width + 1) / (2 * M_PI);
    float v = theta * (this->height + 1) / M_PI;
    return this->bilinInterp(u, v) * sin(theta);
}

Spectrum AmbientLight::sample(glm::vec3& dir) const {
    int index;
    // TODO (repeated calculation of prefix sum)
    Spectrum val = Random::randSelect(width * height, (Spectrum*) colorMap, (Spectrum*) colorMap, index);
    int w = index / height;
    int h = index % height;
    dir = invMap(w + 0.5, h + 0.5);
    return val;
}