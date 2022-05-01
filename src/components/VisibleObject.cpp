#include "components/VisibleObject.h"

VisibleObject::VisibleObject(const BSDF* bsdf, const Transformation& trans): ThreeDObject(trans), material(bsdf) {}

const BSDF* VisibleObject::getMaterial() const {
    return material;
}