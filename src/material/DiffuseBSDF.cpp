#include "material/DiffuseBSDF.h"

DiffuseBSDF::DiffuseBSDF(const Spectrum& color): color(color) {}

const BSDF::BSDFProperty DiffuseBSDF::property() const {
    return BSDF_PROPERTY_CONTINUOUS;
}

Spectrum DiffuseBSDF::f(const glm::vec3& wi, const glm::vec3& wo) const {
    return Spectrum(color);
}

Spectrum DiffuseBSDF::sample(const glm::vec3& wo, glm::vec3& wi) const {
    wi = Random::vecOnHemisphere();
    return Spectrum(color);
}