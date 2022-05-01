#include "TestInclude.h"
#include "components/Camera.h"
using namespace glm;

int main() {
    Camera cam(vec3(1, 0, 0), vec3(0, 1, 0));
    CHECK_EPSILON_EQU(cam.getZ(), vec3(0, -1, 0), 2e-7f);
    CHECK_EPSILON_EQU(cam.getX(), vec3(1, 0, 0), 2e-7f);
    CHECK_EPSILON_EQU(cam.getY(), vec3(0, 0, 1), 2e-7f);
    Ray ray = cam.getRay(vec2(0, 0));
    CHECK_EPSILON_EQU(ray.position(), vec3(1, 0, 0), 2e-7f);
    CHECK_EPSILON_EQU(ray.direction(), vec3(0, 1, 0), 2e-7f);
    ray = cam.getRay(vec2(1, 1));
    CHECK_EPSILON_EQU(ray.position(), vec3(1, 0, 0), 2e-7f);
    CHECK_EPSILON_EQU(ray.direction(), glm::normalize(vec3(1, 1, 1)), 2e-7f);
    cam = Camera(vec3(0, 1, 0), vec3(-1, 0, 0));
    CHECK_EPSILON_EQU(cam.getZ(), vec3(1, 0, 0), 2e-7f);
    CHECK_EPSILON_EQU(cam.getX(), vec3(0, 1, 0), 2e-7f);
    CHECK_EPSILON_EQU(cam.getY(), vec3(0, 0, 1), 2e-7f);
}