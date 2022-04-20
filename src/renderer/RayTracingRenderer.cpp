#include "renderer/RayTracingRenderer.h"

const int RayTracingRenderer::DEFAULT_SAMPLE_NUMBER = 100;
const int RayTracingRenderer::DEFAULT_TRACING_DEPTH = 8;

RayTracingRenderer::RayTracingRenderer(const Scene& scene, int depth, int number, int width, int height)
    : Renderer(scene, width, height), tracingDepth(depth), sampleNumber(number) {
}