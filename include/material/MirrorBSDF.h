#pragma once

#include "material/BSDF.h"

class MirrorBSDF: public BSDF {
public:
    MirrorBSDF(float refl = 1.0f);
    Spectrum f(const glm::vec3& wi, const glm::vec3& wo) const override;
    Spectrum sample(const glm::vec3& wo, glm::vec3& wi) const override;
private:
    float refl; // mirror's reflection factor
};