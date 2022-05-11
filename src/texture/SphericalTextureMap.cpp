#include "texture/SphericalTextureMap.h"

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
    float i = phi * this->width / (2 * M_PI);
    float j = theta * this->height / M_PI;
    return this->bilinInterp(i, j);
}
