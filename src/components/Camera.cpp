#include "components/Camera.h"

const float Camera::DEFAULT_FOCUS = 1.0f;

Camera::Camera(float focus): ThreeDObject(), focus(focus) {}

Camera::Camera(const glm::vec3& pos, const glm::vec3& dirFacing, float focus)
    : ThreeDObject(facing(dirFacing), pos), focus(focus) {}

float Camera::getFocus() const {
    return focus;
}

Ray Camera::getRay(const glm::vec2& pixel) const {
    return Ray(getCenter(), transformation.getRotation() * glm::vec3(pixel.x, pixel.y, -focus));
}

glm::quat Camera::facing(const glm::vec3& dirFacing) {
    glm::vec3 dir = glm::normalize(dirFacing);
    float t1 = asin(hypot(dir.x, dir.y));
    if(dir.z > 0) {
        t1 = M_PI - t1;
    }
    float t2 = atan(dir.x / dir.y);
    if(dir.y < 0) {
        t2 += M_PI;
    }
    return glm::quat(cos(t2 / 2), 0, 0, -sin(t2 / 2)) * glm::quat(cos(t1 / 2), sin(t1 / 2), 0, 0);
}