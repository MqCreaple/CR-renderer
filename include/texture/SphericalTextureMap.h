#pragma once

#include "texture/TextureMap.h"

template<typename T>
class SphericalTextureMap: public TextureMap<T> {
public:
    SphericalTextureMap(size_t width, size_t height);
    virtual T map(const glm::vec3& local) const override;
    glm::vec3 invMap(float u, float v) const override;
};

template<typename T>
SphericalTextureMap<T>::SphericalTextureMap(size_t width, size_t height): TextureMap<T>(width, height) {}

template<typename T>
T SphericalTextureMap<T>::map(const glm::vec3& local) const {
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
    return this->bilinInterp(u, v);
}

template<typename T>
glm::vec3 SphericalTextureMap<T>::invMap(float u, float v) const {
    float phi = u * (2 * M_PI) / (this->width + 1);
    float theta = v * M_PI / (this->height + 1);
    return glm::vec3 (
        sin(theta) * cos(phi),
        sin(theta) * sin(phi),
        cos(theta)
    );
}
