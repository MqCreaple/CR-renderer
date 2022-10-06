#include "components/SphereObject.h"

SphereObject::SphereObject(float radius, const glm::vec3& center, const BSDF* bsdf)
    : VisibleObject(bsdf, Transformation::translation(center)), radius(radius) {}

Tracable::HitResult SphereObject::intersect(const Ray& ray, float tMin, float tMax) const {
    // Define the sphere as $S = (\vec{c}, r)$, and the ray as $R = (\vec{p}, \vec{d})$.
    // Then the $t$ value of the intersection is one of the solutions of this equation:
    // $$||(\vec{p} + t\vec{d}) - \vec{c}|| = r$$
    // which can be simplified to this quadratic equation:
    // $$t^2 - [2(\vec{p}-\vec{c})\cdot\vec{d}]t + [(\vec{p}-\vec{c})^2-r^2] = 0$$

    glm::vec3 tmp = ray.position() - getCenter();
    float hb = glm::dot(tmp, ray.direction());
    float c = glm::dot(tmp, tmp) - radius * radius;
    float delta = hb * hb - c;
    if(delta < 0) {
        return HitResult();
    }
    float t = -hb - sqrt(delta);
    if(t < tMin) {
        t = -hb + sqrt(delta);
    }
    if(t < tMin || t > tMax) {
        return HitResult();
    }
    glm::vec3 i = ray.at(t);                         // intersection
    glm::vec3 n = glm::normalize(i - getCenter());   // normal vector
    return HitResult(i, n, t, this->material);
}