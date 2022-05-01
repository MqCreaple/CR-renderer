#pragma once

#include "components/ThreeDObject.h"
#include "components/Tracable.h"
#include "material/BSDF.h"

class VisibleObject: public ThreeDObject, public Tracable {
public:
    VisibleObject(const BSDF* bsdf = BSDF::DEFAULT, const Transformation& trans = Transformation::DEFAULT);

    const BSDF* getMaterial() const;
protected:
    const BSDF* material;
};