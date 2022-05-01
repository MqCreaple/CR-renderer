#include "TestInclude.h"
#include "components/TriangleMeshObject.h"
#include <iostream>
using namespace std;
using namespace glm;

int main() {
    // Test 1: Single Triangle Surface //
    vector<vec3> v1 ({
        vec3(0, 0, 0),
        vec3(1, 0, 0),
        vec3(0, 1, 0)
    });
    vector<ivec3> s1({ivec3(0, 1, 2)});
    TriangleMeshObject o1(v1, s1);
    CHECK_EPSILON_EQU(o1.getSurface(0).normal(), vec3(0, 0, 1), 2e-7f);
    // ray
    Ray ray(vec3(0, 0, 1), vec3(1, 2, -4));
    Tracable::HitResult result = o1.intersect(ray);
    CHECK(result.valid)
    CHECK_EPSILON_EQU(result.intersection, vec3(0.25, 0.5, 0), 2e-7f);
    CHECK_EPSILON_EQU(result.normal, vec3(0, 0, 1), 2e-7f);
    CHECK_EPSILON_EQU(result.t, sqrt(21) / 4, 2e-7f);
    ray = Ray(vec3(0, 0, 1), vec3(-1, 2, -4));
    result = o1.intersect(ray);
    CHECK(!result.valid);
    ray = Ray(vec3(0, 0, 1), vec3(1, 0, 0));
    result = o1.intersect(ray);
    CHECK(!result.valid);

    // Test 2: Tetrahedron //
    vector<vec3> v2 ({
        vec3(1, 0, 0),
        vec3(0, 1, 0),
        vec3(0, 0, 1),
        vec3(0, 0, -1)
    });
    vector<ivec3> s2 ({
        ivec3(0, 1, 2),
        ivec3(0, 3, 1),
        ivec3(0, 2, 3),
        ivec3(1, 3, 2)
    });
    TriangleMeshObject o2(v2, s2, BSDF::DEFAULT, Transformation(vec3(1, 0, 0), M_PI_2, vec3(1, 2, 3)));
    CHECK_EPSILON_EQU(o2.getSurface(0).localNormal(), normalize(vec3(1, 1, 1)), 2e-7f);
    CHECK_EPSILON_EQU(o2.getSurface(1).localNormal(), normalize(vec3(1, 1, -1)), 2e-7f);
    CHECK_EPSILON_EQU(o2.getSurface(2).localNormal(), vec3(0, -1, 0), 2e-7f);
    CHECK_EPSILON_EQU(o2.getSurface(3).localNormal(), vec3(-1, 0, 0), 2e-7f);
    CHECK_EPSILON_EQU(o2.getSurface(0).normal(), normalize(vec3(1, -1, 1)), 2e-7f);
    CHECK_EPSILON_EQU(o2.getSurface(1).normal(), normalize(vec3(1, 1, 1)), 2e-7f);
    CHECK_EPSILON_EQU(o2.getSurface(2).normal(), vec3(0, 0, -1), 2e-7f);
    CHECK_EPSILON_EQU(o2.getSurface(3).normal(), vec3(-1, 0, 0), 2e-7f);

    // TODO (test toLocal and toWorld)
    
    ray = Ray(vec3(2.5, 2, 2), vec3(-1, 0, 1));
    result = o2.intersect(ray);
    CHECK(result.valid);
    CHECK_EPSILON_EQU(result.intersection, vec3(1.5, 2, 3), 2e-7f);
    CHECK_EPSILON_EQU(result.normal, vec3(0, 0, -1), 2e-7f);
    ray = Ray(vec3(0, 0, 2), vec3(1, 1, -2));
    result = o2.intersect(ray);
    CHECK(!result.valid);
}