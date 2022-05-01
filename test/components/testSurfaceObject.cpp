#include "TestInclude.h"
#include "components/SurfaceObject.h"
using namespace std;
using namespace glm;

int main() {
    SurfaceObject obj(5.0, 5.0);
    Ray ray(vec3(1, 1, 1), vec3(-1, -1, -1));
    Tracable::HitResult result = obj.intersect(ray);
    CHECK(result.valid);
    CHECK_EPSILON_EQU(result.intersection, vec3(0, 0, 0), 2e-7f);
    CHECK_EPSILON_EQU(result.normal, vec3(0, 0, 1), 2e-7f);
    CHECK_EPSILON_EQU(result.t, sqrt(3), 2e-7f);
}