#pragma once

#include "components/ThreeDObject.h"
#include "utils/Spectrum.h"

class PointLight: public ThreeDObject {
public:
    PointLight(const Spectrum& s, const glm::vec3& pos = glm::vec3(0, 0, 0));

    Spectrum getIllumination() const;
private:
    Spectrum illumination;
};