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
        Scene* scene,
        float fogDensity = 0.0f,
        int depth = DEFAULT_TRACING_DEPTH,
        int number = DEFAULT_SAMPLE_NUMBER,
        int width = WINDOW_DEFAULT_WIDTH,
        int height = WINDOW_DEFAULT_HEIGHT
    );

    /**
     * @brief render the window.
     */
    void render() override;
private:
    int tracingDepth;
    int sampleNumber;
    float fogDensity;     // density of fog, a number between 0 and 1
    Spectrum traceIndirect(const Ray& ray, int depth) const;
    Spectrum traceDirect(const Tracable::HitResult& result, const glm::quat& q, const glm::vec3& wo) const;
};