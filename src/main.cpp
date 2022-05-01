#include "CRrenderer.h"
#include <chrono>
#include <thread>
#include <csignal>
using namespace glm;
using namespace std;

int main() {
    MirrorBSDF mirrorBSDF(1);
    SphereObject object(1, vec3(0, 0, 1));
    SphereObject obj2(1.5, vec3(-1, 2, 1.5), &mirrorBSDF);
    SurfaceObject ground(5, 5);
    Camera camera(vec3(3, 0, 1), glm::normalize(vec3(-3, 0, -1)), 0.5);
    Scene scene(camera);
    scene.getObjects()->add(ground);
    scene.getObjects()->add(object);
    scene.getObjects()->add(obj2);
    PointLight l1(Spectrum(2), vec3(0, 0, 3));
    PointLight l2(Spectrum(0.8), vec3(2, 1, 0.8));
    scene.getLights().push_back(&l1);
    scene.getLights().push_back(&l2);
    RayTracingRenderer renderer(&scene);
    renderer.render();
    renderer.update();
    renderer.main();
}