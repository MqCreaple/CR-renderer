#include "light/PointLight.h"

PointLight::PointLight(const Spectrum& s, const glm::vec3& pos)
    : ThreeDObject(Transformation::translation(pos)), illumination(s) {}

Spectrum PointLight::getIllumination() const {
    return illumination;
}