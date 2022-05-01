#pragma once

#include "components/VisibleObject.h"

/**
 * @brief Rectangle surface object.
 * The default surface is on the xOy plane with center at the origin. Its normal vector is [0, 0, 1].
 */
class SurfaceObject: public VisibleObject {
public:
    SurfaceObject (
        float width,
        float height,
        const BSDF* bsdf = BSDF::DEFAULT,
        const Transformation& t = Transformation::DEFAULT
    );

    HitResult intersect(const Ray& ray, float tMin = DEFAULT_T_MIN, float tMax = DEFAULT_T_MAX) const override;
private:
    float halfX;
    float halfY;
};