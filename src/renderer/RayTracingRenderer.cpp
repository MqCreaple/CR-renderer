#include "renderer/RayTracingRenderer.h"

const int RayTracingRenderer::DEFAULT_SAMPLE_NUMBER = 700;
const int RayTracingRenderer::DEFAULT_TRACING_DEPTH = 4;

RayTracingRenderer::RayTracingRenderer(Scene* scene, float fogDensity, int depth, int number, int width, int height)
    : Renderer(scene, width, height), fogDensity(fogDensity), tracingDepth(depth), sampleNumber(number) {}

void RayTracingRenderer::render() {
    Camera camera = scene->getPrimaryCamera();
    for(int i = 0; i < windowWidth; i++) {
        for(int j = 0; j < windowHeight; j++) {
            // loop through every pixel
            std::pair<glm::vec2, glm::vec2> pos = pixel(i, j);
            Color pixelColor(0);
            for(int k = 0; k < sampleNumber; k++) {                    // sample multiple times
                glm::vec2 samplePos (
                    Random::uniform(pos.first.x, pos.second.x),
                    Random::uniform(pos.first.y, pos.second.y)
                );                                                     // choose a random point inside the pixel
                Ray ray = camera.getRay(samplePos);                    // get the outward ray
                pixelColor += Color(traceIndirect(ray, tracingDepth)); // trace ray color
            }
            setPixel(i, j, pixelColor / (sampleNumber * 1.0f));
        }
        update();  //! REMOVE THIS LINE IN FINAL RELEASE
    }
    std::cout << "[info] Render completed!" << std::endl;
}

Spectrum RayTracingRenderer::traceIndirect(const Ray& ray, int depth) const {
    Tracable::HitResult result = scene->getObjects()->intersect(ray);
    if(!result.valid) {
        if(scene->getAmbientLight() != nullptr) {
            return scene->getAmbientLight()->map(ray.direction());
        }
        return Spectrum(0);
    }
    // fog reflection
    if(fogDensity > 0) {
        float rand = Random::uniform();
        float distance = log(1 - rand) / log(1 - fogDensity);
        if(distance < result.t) {
            return traceIndirect(Ray(ray.at(distance), Random::unitVec()), depth - 1);
        }
    }

    glm::vec3 axis = (result.normal.z == -1)? glm::vec3(1, 0, 0): glm::normalize(result.normal + glm::vec3(0, 0, 1));
    glm::quat q(0, axis); // transformation from world coordinate to surface's local coordinte (normal vector -> [0, 0, 1])

    glm::vec3 oDir = -(q * ray.direction()); // local

    float direct = traceDirect(result, q, oDir);
    if(depth <= 1 && result.material->property() == BSDF::BSDF_PROPERTY_CONTINUOUS) {
        return direct;
    } else if(depth <= 0) {
        return Spectrum(0);
    }
    glm::vec3 iDir;  // local
    Spectrum s = result.material->sample(oDir, iDir);
    iDir = iDir * q; // world
    float indirect =  s * traceIndirect(Ray(result.intersection, iDir), depth - 1) * glm::dot(iDir, result.normal);  // Lo(wo) = Li(wi) * f(wi, wo) * cos(theta)
    return direct + indirect;                                                                                        // trace both direct and indirect light and return their sum
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

    // trace ambient light
    AmbientLight* ambient = scene->getAmbientLight();
    if(ambient != nullptr) {
        glm::vec3 dir;
        Spectrum s = ambient->sample(dir);
        float proj = glm::dot(dir, n);
        if(proj < 0) {
            proj = 0;
        }
        Ray ray(result.intersection, dir);
        Tracable::HitResult r = scene->getObjects()->intersect(ray);
        if(!r.valid) {
            ans += s * proj;
        }
    }
    return ans;
}