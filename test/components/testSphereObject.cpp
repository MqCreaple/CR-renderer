#include "TestInclude.h"
#include "components/SphereObject.h"
#include <glm/glm.hpp>
using namespace std;
using namespace glm;

int main() {
    SphereObject sphere(1, vec3(0, 0, 0));
    Ray ray(vec3(-10, 0, 0), vec3(1, 0, 0));
    TracableObject::HitResult result = sphere.intersect(ray);
    CHECK(result.valid);
    CHECK_EPSILON_EQU(result.intersection, vec3(-1, 0, 0), 2e-7f);
    CHECK_EPSILON_EQU(result.normal, vec3(-1, 0, 0), 2e-7f);
    CHECK_EPSILON_EQU(result.t, 9, 2e-7f);

    ray = Ray(vec3(2, 0, 0), vec3(0, 1, 0));
    result = sphere.intersect(ray);
    CHECK(!result.valid);

    ray = Ray(vec3(-10, 0, 0), vec3(-1, 0, 0));
    result = sphere.intersect(ray);
    CHECK(!result.valid);

    ray = Ray(vec3(0, 10, 0), vec3(0, -1, 0));
    result = sphere.intersect(ray, 0, 5);
    CHECK(!result.valid);
    result = sphere.intersect(ray, 0, 100);
    CHECK(result.valid);
    CHECK_EPSILON_EQU(result.intersection, vec3(0, 1, 0), 2e-7f);
    CHECK_EPSILON_EQU(result.normal, vec3(0, 1, 0), 2e-7f);

    SphereObject s2(1, vec3(1, 0, 0));
    ray = Ray(vec3(-10, 0, 0), vec3(1, 0, 0));
    result = s2.intersect(ray);
    CHECK(result.valid);
    CHECK_EPSILON_EQU(result.intersection, vec3(0, 0, 0), 2e-7f);
    CHECK_EPSILON_EQU(result.t, 10, 2e-7f);
}