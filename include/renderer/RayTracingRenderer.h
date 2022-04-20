#pragma once

#include "utils/Ray.h"
#include "renderer/Renderer.h"
#include "utils/Spectrum.h"
#include <glm/glm.hpp>

class RayTracingRenderer: public Renderer {
public:
    static const int DEFAULT_TRACING_DEPTH;
    static const int DEFAULT_SAMPLE_NUMBER;
    RayTracingRenderer (
        const Scene& scene,
        int depth = DEFAULT_TRACING_DEPTH,
        int number = DEFAULT_SAMPLE_NUMBER,
        int width = WINDOW_DEFAULT_WIDTH,
        int height = WINDOW_DEFAULT_HEIGHT
    );

    /**
     * @brief trace the spectrum of one pixel
     * @param pixel position of pixel in fragment coordinate
     * @return Spectrum spectrum of that pixel
     */
    Spectrum tracePixel(const glm::vec2& pixel);

    /**
     * @brief render the window.
     */
    void render();
private:
    int tracingDepth;
    int sampleNumber;
    Spectrum _trace(const Ray&, int depth);
};