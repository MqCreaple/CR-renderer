#pragma once

#include "utils/Spectrum.h"
#include "utils/Random.h"

/**
 * @brief interface for BSDF materials.
 */
class BSDF {
public:
    static const BSDF* DEFAULT;

    /**
     * @brief The value of reflection function with given incoming and outgoing ray direction.
     * surface's normal vector is [0, 0, 1].
     * @param wi incoming ray direction.
     * @param wo outgoing ray direction.
     * @return Spectrum reflection function
     */
    virtual Spectrum f(const glm::vec3& wi, const glm::vec3& wo) const = 0;

    /**
     * @brief For a given outgoing direction, returns a incoming direction and the attenuation factor.
     * For ideal mirror, wi is the reflection of wo and attenuation factor of every wavelength is 1.
     * For other material, wi is a random direction and attenuation factor is the value of reflection function.
     * @param wo outgoing direction.
     * @param wi returned incoming direction.
     * @return Spectrum attenuation factor of every color.
     */
    virtual Spectrum sample(const glm::vec3& wo, glm::vec3& wi) const = 0;
};