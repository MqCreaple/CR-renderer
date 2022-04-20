#include "TestInclude.h"
#include "utils/Ray.h"
#include <glm/glm.hpp>
using namespace std;
using namespace glm;

int main() {
    Ray ray(vec3(0, 1, 2), vec3(2, 3, 6));
    CHECK_EPSILON_EQU(ray.at(7), vec3(2, 4, 8), 2e-7f);
}