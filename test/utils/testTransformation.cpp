#include "TestInclude.h"
#include "utils/Transformation.h"
#include "utils/Random.h"
#include <iostream>
#include <cmath>
using namespace std;
using namespace glm;

int main() {
    vec3 v(1, 0, 0);
    Transformation tr = Transformation::rotation(vec3(0, 1, 0), M_PI_2);       // rotation around [0, 1, 0] by 90 degrees
    CHECK_EPSILON_EQU(tr.transform(v), vec3(0, 0, -1), 2e-7f);
    CHECK_EPSILON_EQU(tr.invTransform(v), vec3(0, 0, 1), 2e-7f);
    v = vec3(2, 3, 1);
    CHECK_EPSILON_EQU(tr.transform(v), vec3(1, 3, -2), 2e-7f);
    CHECK_EPSILON_EQU(tr.invTransform(v), vec3(-1, 3, 2), 2e-7f);

    Transformation tt = Transformation::translation(vec3(1, 2, -3));           // translation by vector [1, 2, -3]
    v = vec3(4, 6, 2);
    CHECK_EPSILON_EQU(tt.transform(v), vec3(5, 8, -1), 2e-7f);
    CHECK_EPSILON_EQU(tt.invTransform(v), vec3(3, 4, 5), 2e-7f);

    Transformation tc = Transformation(vec3(0, 1, 0), M_PI_2, vec3(1, 2, 3));  // rotation around [0, 1, 0] by 90 degrees then translate by [1, 2, 3]
    v = vec3(4, 6, 2);
    CHECK_EPSILON_EQU(tc.transform(v), vec3(3, 8, -1), 2e-7f);
    CHECK_EPSILON_EQU(tc.invTransform(v), vec3(1, 4, 3), 2e-7f);

    // test the inverse transformation
    const size_t N = 1000;
    for(int i = 0; i < N; i++) {
        v = Random::unitVec() * Random::uniform();
        CHECK_EPSILON_EQU(v, tc.transform(tc.inv().transform(v)), 2e-7f);
    }
    return 0;
}