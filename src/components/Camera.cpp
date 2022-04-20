#include "components/Camera.h"

const float Camera::DEFAULT_FOCUS = 1.0;

Camera::Camera(): focus(DEFAULT_FOCUS) {}
Camera::Camera(float focus): focus(focus) {}

float Camera::getFocus() const {
    return focus;
}

Ray Camera::getRay(const glm::vec2& pixel) const {
    return Ray(getCenter(), glm::vec3(pixel.x, pixel.y, -focus));
}