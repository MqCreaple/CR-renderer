#include "utils/Transformation.h"

// static members

const Transformation Transformation::DEFAULT = Transformation();

// public methods

Transformation::Transformation(): rotate(1.0f, 0.0f, 0.0f, 0.0f), translate(0.0f, 0.0f, 0.0f) {}

Transformation::Transformation(const glm::quat& q, const glm::vec3& v): rotate(q), translate(v) {}

Transformation::Transformation(const glm::vec3& axis, float angle, const glm::vec3& v)
    : rotate(glm::cos(angle / 2), glm::normalize(axis) * glm::sin(angle / 2)), translate(v) {}

glm::quat Transformation::getRotation() const { return rotate; }

glm::vec3 Transformation::getTranslation() const { return translate; }

Transformation Transformation::inv() const {
    glm::vec3 tNew = translate * rotate;
    return Transformation(glm::conjugate(rotate), -translate * rotate);
}

glm::vec3 Transformation::transform(const glm::vec3& v) const {
    return rotate * v + translate;
}

glm::vec3 Transformation::invTransform(const glm::vec3& v) const {
    return (v - translate) * rotate;
}

glm::mat4 Transformation::getTransformationMatrix() const {
    return glm::mat4 (
        1, 0, 0, translate.x,
        0, 1, 0, translate.y,
        0, 0, 1, translate.z,
        0, 0, 0, 1
    ) * glm::mat4_cast(rotate);
}

glm::mat4 Transformation::getInvTransformationMatrix() const {
    return glm::mat4_cast(glm::conjugate(rotate)) * glm::mat4 (
        1, 0, 0, -translate.x,
        0, 1, 0, -translate.y,
        0, 0, 1, -translate.z,
        0, 0, 0, 1
    );
}

Transformation Transformation::rotation(const glm::vec3& n, float angle) {
    return Transformation(glm::quat(glm::cos(angle / 2), glm::normalize(n) * glm::sin(angle / 2)), glm::vec3());
}

Transformation Transformation::translation(const glm::vec3& tr) {
    return Transformation(glm::quat(1, 0, 0, 0), tr);
}

Transformation Transformation::compose(const Transformation& first, const Transformation& second) {
    return Transformation(second.rotate * first.rotate, second.rotate * first.translate + second.translate);
}