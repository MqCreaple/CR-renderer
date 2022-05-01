#include "components/ThreeDObject.h"

ThreeDObject::ThreeDObject(const Transformation& trans): transformation(trans) {}
ThreeDObject::ThreeDObject(const glm::quat& q, const glm::vec3& v): transformation(q, v) {}

Transformation ThreeDObject::getTransformation() const {
    return transformation;
}

void ThreeDObject::setTransformation(const Transformation& trans) {
    transformation = trans;
}

glm::vec3 ThreeDObject::getX() const {
    return transformation.rotate * glm::vec3(1, 0, 0);
}

glm::vec3 ThreeDObject::getY() const {
    return transformation.rotate * glm::vec3(0, 1, 0);
}

glm::vec3 ThreeDObject::getZ() const {
    return transformation.rotate * glm::vec3(0, 0, 1);
}

glm::vec3 ThreeDObject::toWorldCoord(const glm::vec3& local) const {
    return transformation.transform(local);
}

glm::vec3 ThreeDObject::toLocalCoord(const glm::vec3& world) const {
    return transformation.invTransform(world);
}

glm::vec3 ThreeDObject::getCenter() const {
    return transformation.translate;
}