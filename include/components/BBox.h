#pragma once

#include "components/ThreeDObject.h"
#include "components/TracableObject.h"
#include <vector>

/**
 * @brief Defines a bounding box of an object.
 */
class BBox: public ThreeDObject {
public:
    /**
     * @brief Construct a new bounding box from corners
     * @param bound1 one corner of the box
     * @param bound2 another corner of the box
     * @param transformation transformation
     */
    BBox(const glm::vec3& bound1, const glm::vec3& bound2, const Transformation& transformation = Transformation::DEFAULT);
    /**
     * @brief Construct a bounding box from vertex array
     * @param vertices vertex array
     * @param transformation transformation
     */
    BBox(const std::vector<glm::vec3>& vertices, const Transformation& transformation = Transformation::DEFAULT);

    /**
     * @brief If a ray intersects with the bounding box or not.
     * @param ray a incoming ray
     * @param tMin minimum t value allowed
     * @param tMax maximum t value allowed
     * @return true ray intersects with the box
     * @return false ray does not intersect with the box
     */
    bool intersect(const Ray& ray, float tMin, float tMax) const;
private:
    glm::vec3 bounds[2];
};