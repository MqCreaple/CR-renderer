#pragma once

#include "utils/Transformation.h"

/**
 * @brief Interface for all three dimentional objects.
 */
class ThreeDObject {
public:
    ThreeDObject();
    ThreeDObject(const Transformation& trans);
    ThreeDObject(const glm::quat& q, const glm::vec3& v);

    Transformation getTransformation() const;
    void setTransformation(const Transformation& trans);
    /**
     * @brief Convert local coordinate into world coordinate.
     * @param local point in local coordinate
     * @return glm::vec3 point in world coordinate
     */
    glm::vec3 toWorldCoord(const glm::vec3& local) const;
    /**
     * @brief Convert world coordinate into local coordinate.
     * @param world point in world coordinate
     * @return glm::vec3 point in local coordinate
     */
    glm::vec3 toLocalCoord(const glm::vec3& world) const;

    /**
     * @brief Get the position of center in world coordinate (point [0, 0, 0])
     * @return glm::vec3 center in world coordinate
     */
    glm::vec3 getCenter() const;
protected:
    /**
     * @brief transformation from object to world coordinate
     */
    Transformation transformation;
private:
};