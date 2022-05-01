#pragma once

#include "components/ThreeDObject.h"
#include "material/BSDF.h"
#include "utils/Ray.h"

/**
 * @brief Interface for all 3D objects that can intersect with a ray.
 */
class Tracable {
public:
    static const float DEFAULT_T_MIN;
    static const float DEFAULT_T_MAX;

    /**
     * @brief Record the information of ray hitting an object.
     * Information includes:
     * * valid: whether the intersection exists or not
     * * intersection: intersection (if exists)
     * * normal: normal vector of the surface (if exists)
     * * t: distance from the origin of ray to the intersection (if exists)
     * * material: material of the surface (if exists)
     */
    struct HitResult {
        bool valid;
        glm::vec3 intersection;
        glm::vec3 normal;
        float t;
        const BSDF* material;

        /**
         * @brief Construct an invalid trace result
         */
        HitResult();
        /**
         * @brief Construct an valid trace result with parameters
         * @param intersection intersection
         * @param normal normal vector
         * @param t t value
         * @param material material
         */
        HitResult(const glm::vec3& intersection, const glm::vec3& normal, float t, const BSDF* material);
    };

    /**
     * @brief get the intersection with a ray
     * @param ray incoming ray
     * @return TraceResult trace result
     */
    virtual HitResult intersect(const Ray& ray, float tMin = DEFAULT_T_MIN, float tMax = DEFAULT_T_MAX) const = 0;

    friend class ObjectList;
};