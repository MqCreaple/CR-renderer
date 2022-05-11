#include "renderer/RayTracingRenderer.h"

const int RayTracingRenderer::DEFAULT_SAMPLE_NUMBER = 600;
const int RayTracingRenderer::DEFAULT_TRACING_DEPTH = 4;

RayTracingRenderer::RayTracingRenderer(Scene* scene, int depth, int number, int width, int height)
    : Renderer(scene, width, height), tracingDepth(depth), sampleNumber(number) {}

void RayTracingRenderer::render() {
    Camera camera = scene->getPrimaryCamera();
    for(int i = 0; i < windowWidth; i++) {
        for(int j = 0; j < windowHeight; j++) {
            std::pair<glm::vec2, glm::vec2> pos = pixel(i, j);
            Color pixelColor(0);
            for(int depth = 1; depth <= tracingDepth; depth++) {
                for(int k = 0; k < sampleNumber; k++) {
                    glm::vec2 samplePos (
                        Random::uniform(pos.first.x, pos.second.x),
                        Random::uniform(pos.first.y, pos.second.y)
                    );                                                   // choose a random sample
                    Ray ray = camera.getRay(samplePos);                  // get the outward ray
                    pixelColor += Color(traceIndirect(ray, depth));      // trace ray color
                }
            }
            setPixel(i, j, pixelColor / (sampleNumber * 1.0f));
        }
        update();  //! REMOVE THIS LINE IN FINAL RELEASE
    }
    std::cout << "[info] Render completed!" << std::endl;
}

Spectrum RayTracingRenderer::traceIndirect(const Ray& ray, int depth) const {
    // TODO (trace light whose depth <= tracingDepth in the function)
    Tracable::HitResult result = scene->getObjects()->intersect(ray);
    if(!result.valid) {
        if(scene->getAmbientLight() != nullptr) {
            return scene->getAmbientLight()->map(ray.direction());
        } else {
            return Spectrum(0);
        }
    }

    glm::vec3 axis = (result.normal.z == -1)? glm::vec3(1, 0, 0): glm::normalize(result.normal + glm::vec3(0, 0, 1));
    glm::quat q(0, axis); // transformation from world coordinate to surface's local coordinte (normal vector -> [0, 0, 1])

    glm::vec3 oDir = -(q * ray.direction()); // local

    if(depth <= 1 && result.material->property() == BSDF::BSDF_PROPERTY_CONTINUOUS) {
        return traceDirect(result, q, oDir);
    } else if(depth <= 0) {
        return Spectrum(0);
    }
    glm::vec3 iDir;  // local
    Spectrum s = result.material->sample(oDir, iDir);
    iDir = iDir * q; // world
    return s * traceIndirect(Ray(result.intersection, iDir), depth - 1) * glm::dot(iDir, result.normal);
}

Spectrum RayTracingRenderer::traceDirect(const Tracable::HitResult& result, const glm::quat& q, const glm::vec3& wo) const {
    Spectrum ans(0);
    glm::vec3 p = result.intersection;
    glm::vec3 n = result.normal;
    const BSDF* material = result.material;

    // trace all point lights
    for(PointLight* light : scene->getLights()) {
        glm::vec3 dir = light->getCenter() - p; // world
        if(glm::dot(n, dir) <= 0) {
            continue;
        }
        float d = glm::length(dir);
        dir /= d;                     // world
        glm::vec3 dirLocal = q * dir; // local
        Tracable::HitResult r = scene->getObjects()->intersect(Ray(p, dir));
        if(!r.valid || r.t >= d) {
            // if no object blocks the light //
            ans += material->f(dirLocal, wo) * light->getIllumination() * glm::dot(n, dir) / (d * d);
        }
    }

    AmbientLight* ambient = scene->getAmbientLight();
    if(ambient != nullptr) {
        glm::vec3 dir;
        Spectrum s = ambient->sample(dir);
        float proj = glm::dot(dir, n);
        if(proj < 0) {
            proj = 0;
        }
        Ray ray(result.intersection, dir);
        Tracable::HitResult result = scene->getObjects()->intersect(ray);
        if(!result.valid) {
            ans += ambient->getSum() * proj;
        }
    }
    return ans;
}