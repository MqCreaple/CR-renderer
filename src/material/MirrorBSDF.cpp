#include "material/MirrorBSDF.h"

MirrorBSDF::MirrorBSDF(float refl): refl(refl) {}

const BSDF::BSDFProperty MirrorBSDF::property() const {
    return BSDF_PROPERTY_DISCRETE;
}

Spectrum MirrorBSDF::f(const glm::vec3& wi, const glm::vec3& wo) const {
    /*
    // glm::vec3 v = wi + wo;
    // if(v.x == 0.0f && v.y == 0.0f) {
    //     return Spectrum(INFINITY);
    // }
    */
    return Spectrum(0);
}

Spectrum MirrorBSDF::sample(const glm::vec3& wo, glm::vec3& wi) const {
    wi = glm::vec3(-wo.x, -wo.y, wo.z);
    return Spectrum(refl) / wi.z;
}