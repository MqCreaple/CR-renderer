#include "material/GlassBSDF.h"

GlassBSDF::GlassBSDF(float iof): iof(iof) {}

const BSDF::BSDFProperty GlassBSDF::property() const {
    return BSDF::BSDF_PROPERTY_DISCRETE;
}

Spectrum GlassBSDF::f(const glm::vec3& wi, const glm::vec3& wo) const {
    return Spectrum(0);
}

Spectrum GlassBSDF::sample(const glm::vec3 &wo, glm::vec3 &wi) const {
    if(wo.z > 0) {
        wi.x = -wo.x / iof;
        wi.y = -wo.y / iof;
        wi.z = -sqrt(1 - wi.x * wi.x - wi.y * wi.y);
        return 1; // TODO
    }
    wi.x = -wo.x * iof;
    wi.y = -wo.y * iof;
    wi.z = sqrt(1 - wi.x * wi.x - wi.y * wi.y);
    if(isnanf(wi.z)) {
        return 0;
    }
    return 1;
}