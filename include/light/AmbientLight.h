#pragma once

#include "texture/SphericalTextureMap.h"
#include "utils/Spectrum.h"
#include "utils/Random.h"

class AmbientLight: public SphericalTextureMap<Spectrum> {
public:
    AmbientLight(size_t width, size_t height);
    void set(int i, int j, Spectrum val) override;

    /**
     * @brief Get the sum of all pixels
     * @return Spectrum sum of all pixels
     */
    Spectrum getSum() const;

    Spectrum map(const glm::vec3& local) const override;

    /**
     * @brief sample the direction by light intensity.
     * Area with higher light intensity will have a higher chance to be sampled, vice versa.
     * @param dir sampled direction
     * @return Spectrum spectrum on that direction
     */
    Spectrum sample(glm::vec3& dir) const;
private:
    Spectrum sum;
};