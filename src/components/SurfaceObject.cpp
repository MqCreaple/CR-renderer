#include "components/SurfaceObject.h"

SurfaceObject::SurfaceObject(float width, float height, const BSDF* bsdf, const Transformation& t)
    : VisibleObject(bsdf, t), halfX(width / 2), halfY(height / 2) {}

Tracable::HitResult SurfaceObject::intersect(const Ray& ray, float tMin, float tMax) const {
    glm::vec3 localPos = toLocalCoord(ray.position());
    glm::vec3 localDir = ray.direction() * transformation.getRotation();
    float t = -localPos.z / localDir.z;
    if(t < tMin || t > tMax) {
        return HitResult();
    }
    float x = localPos.x + t * localDir.x;
    float y = localPos.y + t * localDir.y;
    if(abs(x) > halfX || abs(y) > halfY) {
        return HitResult();
    }
    glm::vec3 normal = transformation.getRotation() * glm::vec3(0, 0, ((localPos.z > 0)? 1: -1));
    return HitResult(ray.at(t), normal, t, this->material);
}