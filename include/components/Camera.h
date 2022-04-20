#pragma once

#include "components/ThreeDObject.h"
#include "utils/Ray.h"

/**
 * @brief Defines a model of simple pinhole camera
 */
class Camera: public ThreeDObject {
public:
    Camera();
    Camera(float focus);

    /**
     * @brief Get the focus value (distance from the screen to the pinhole)
     * @return float focus
     */
    float getFocus() const;
    /**
     * @brief Get the outgoing ray coming out of a given pixel
     * @param pixel position of pixel in fragment coordinate
     * @return Ray outgoing ray from the pixel.
     */
    Ray getRay(const glm::vec2& pixel) const;

    static const float DEFAULT_FOCUS;
private:
    float focus;
};