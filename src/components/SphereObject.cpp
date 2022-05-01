#include "components/SphereObject.h"

SphereObject::SphereObject(float radius, const glm::vec3& center, const BSDF* bsdf)
    : VisibleObject(bsdf, Transformation::translation(center)), radius(radius) {}

Tracable::HitResult SphereObject::intersect(const Ray& ray, float tMin, float tMax) const {
    glm::vec3 tmp = ray.position() - getCenter();
    float hb = glm::dot(tmp, ray.direction());
    float c = glm::dot(tmp, tmp) - radius * radius;
    float delta = hb * hb - c;
    if(delta < 0) {
        return HitResult();
    }
    bool in = false;
    float t = -hb - sqrt(delta);
    if(t < tMin) {
        in = true;
        t = -hb + sqrt(delta);
    }
    if(t < tMin || t > tMax) {
        return HitResult();
    }
    glm::vec3 i = ray.at(t);
    glm::vec3 n = in? (getCenter() - i) / radius: (i - getCenter()) / radius;
    return HitResult(i, n, t, this->material);
}