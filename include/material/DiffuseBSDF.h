#pragma once

#include "material/BSDF.h"

class DiffuseBSDF: public BSDF {
public:
    DiffuseBSDF(const Spectrum& color = Spectrum(1.0f));
    const BSDFProperty property() const override;
    Spectrum f(const glm::vec3& wi, const glm::vec3& wo) const override;
    Spectrum sample(const glm::vec3& wo, glm::vec3& wi) const override;
private:
    Spectrum color;
};