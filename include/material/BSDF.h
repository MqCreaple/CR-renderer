#pragma once

#include <cmath>
#include "utils/Spectrum.h"
#include "utils/Random.h"

/**
 * @brief interface for BSDF materials.
 */
class BSDF {
public:
    static const BSDF* DEFAULT;

    /**
     * property of the scattering function
     */
    enum BSDFProperty {
        BSDF_PROPERTY_DISCRETE,    // discrete (mirror, glass, ...)
        BSDF_PROPERTY_CONTINUOUS   // continuous (diffuse material, metal, ...)
    };

    virtual const BSDFProperty property() const = 0;

    /**
     * @brief The value of reflection function with given incoming and outgoing ray direction.
     * In local coordinate, surface's normal vector is [0, 0, 1].
     * @param wi (local) incoming ray direction.
     * @param wo (local) outgoing ray direction.
     * @return Spectrum reflection function
     */
    virtual Spectrum f(const glm::vec3& wi, const glm::vec3& wo) const = 0;

    /**
     * @brief For a given outgoing direction, returns a incoming direction and the attenuation factor.
     * For discrete material, attenuation factor is the probability of choosing a specific output direction.
     * For continuous material, wi is a random direction and attenuation factor is the value of reflection function at (wi, wo).
     * @param wo (local) outgoing direction.
     * @param wi (local) returned incoming direction.
     * @return Spectrum attenuation factor of every color.
     */
    virtual Spectrum sample(const glm::vec3& wo, glm::vec3& wi) const = 0;
};