#include "CRrenderer.h"
#include <ctime>
#include <chrono>
#include <thread>
#include <csignal>
using namespace glm;
using namespace std;
using namespace std::chrono;

int main() {
    MirrorBSDF mirrorBSDF(1);
    SurfaceObject s1(10, 10);
    SurfaceObject s2(6, 10, BSDF::DEFAULT, Transformation(quat(M_SQRT1_2, 0, M_SQRT1_2, 0), vec3(-5, 0, 3)));
    SurfaceObject s3(10, 6, BSDF::DEFAULT, Transformation(quat(M_SQRT1_2, M_SQRT1_2, 0, 0), vec3(0, 5, 3)));
    SphereObject sp1(2, vec3(-2, -2, 2));
    SphereObject sp2(2, vec3(2, 2, 2), &mirrorBSDF);
    Camera cam(vec3(0, -7, 4), vec3(0, 7, -4));
    AmbientLight ambient(20, 10);
    ambient.set(18, 2, Spectrum(0.95));
    PointLight point(0.5, vec3(0, 0, 1));
    Scene scene(cam, &ambient);
    scene.getObjects()->add(s1);
    scene.getObjects()->add(s2);
    scene.getObjects()->add(s3);
    scene.getObjects()->add(sp1);
    scene.getObjects()->add(sp2);
    // scene.getLights().push_back(&point);
    RayTracingRenderer renderer(&scene);
    steady_clock::time_point t1 = steady_clock::now();
    renderer.render();
    steady_clock::time_point t2 = steady_clock::now();
    duration<double> d = duration_cast<duration<double>>(t2 - t1);
    renderer.update();
    cout << "[info] time taken: " << d.count() << endl;
    renderer.main();
}