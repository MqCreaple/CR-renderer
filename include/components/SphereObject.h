#pragma once

#include "components/VisibleObject.h"
#include <cmath>

class SphereObject: public VisibleObject {
public:
    SphereObject(float radius, const glm::vec3& center = glm::vec3(0, 0, 0), const BSDF* bsdf = BSDF::DEFAULT);
    HitResult intersect(const Ray& ray, float tMin = DEFAULT_T_MIN, float tMax = DEFAULT_T_MAX) const override;
private:
    float radius;
};