#include "components/TracableObject.h"

const float TracableObject::DEFAULT_T_MIN = 0;
const float TracableObject::DEFAULT_T_MAX = INFINITY;

TracableObject::TracableObject(const Transformation& transformation): ThreeDObject(transformation) {}

TracableObject::HitResult::HitResult(): valid(false), intersection(), normal(), t() {}

TracableObject::HitResult::HitResult(const glm::vec3& intersection, const glm::vec3& normal, float t)
    : valid(true), intersection(intersection), normal(normal), t(t) {}