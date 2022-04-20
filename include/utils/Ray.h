#pragma once

#include <glm/glm.hpp>

/**
 * @brief Ray from a specific position and direction.
 * The ray is described by parametric equation: (pos) + t * (dir).
 * The position and direction are always described in world coordinate.
 */
class Ray { 
public:
    /**
     * @brief Construct a standard Ray object
     */
    Ray();

    /**
     * @brief Construct a Ray from position and direction vector
     * @param p position vector
     * @param d direction vector
     */
    Ray(const glm::vec3& p, const glm::vec3& d);

    /**
     * @brief get the position of ray
     * @return glm::vec3 position
     */
    glm::vec3 position() const;

    /**
     * @brief get the direction of ray
     * @return glm::vec3 direction
     */
    glm::vec3 direction() const;

    /**
     * @brief Get the point @c dist far along the ray's direction.
     * @param dist distance of the point to @c pos
     * @return glm::vec3 point
     */
    glm::vec3 at(float dist) const;
private:
    glm::vec3 pos;
    glm::vec3 dir;
};