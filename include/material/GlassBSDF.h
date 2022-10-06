#pragma once

#include "material/BSDF.h"

class GlassBSDF: public BSDF {
public:
    GlassBSDF(float iof = 1.5);
    const BSDFProperty property() const override;
    Spectrum f(const glm::vec3& wi, const glm::vec3& wo) const override;
    Spectrum sample(const glm::vec3& wo, glm::vec3& wi) const override;
private:
    float iof;  // index of refraction / refractive index
};