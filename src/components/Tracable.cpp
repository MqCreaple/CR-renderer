#include "components/Tracable.h"

const float Tracable::DEFAULT_T_MIN = 2e-6f;
const float Tracable::DEFAULT_T_MAX = INFINITY;

Tracable::HitResult::HitResult(): valid(false), intersection(), normal(), t() {}

Tracable::HitResult::HitResult(const glm::vec3& intersection, const glm::vec3& normal, float t, const BSDF* material)
    : valid(true), intersection(intersection), normal(normal), t(t), material(material) {}