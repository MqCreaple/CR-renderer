#pragma once

#include "components/ThreeDObject.h"
#include "components/TracableObject.h"
#include <cmath>

class SphereObject: public TracableObject {
public:
    SphereObject(float radius, const glm::vec3& center = glm::vec3(0, 0, 0));
    HitResult intersect(const Ray& ray, float tMin = DEFAULT_T_MIN, float tMax = DEFAULT_T_MAX) const override;
private:
    float radius;
};