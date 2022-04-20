#include "utils/Ray.h"

Ray::Ray(): pos(), dir(1, 0, 0) {}

Ray::Ray(const glm::vec3& p, const glm::vec3& d): pos(p), dir(glm::normalize(d)) {}

glm::vec3 Ray::position() const {
    return pos;
}

glm::vec3 Ray::direction() const {
    return dir;
}

glm::vec3 Ray::at(float dist) const {
    return pos + dist * dir;
}