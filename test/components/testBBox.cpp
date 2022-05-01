#include "TestInclude.h"
#include "components/BBox.h"
#include "components/Tracable.h"
#include "utils/Random.h"
using namespace std;
using namespace glm;

int main() {
    BBox box(vec3(-1, -1, -1), vec3(1, 1, 1));
    Ray ray(vec3(2, 0, 0), vec3(-1, 0, 0));
    CHECK(box.intersect(ray, Tracable::DEFAULT_T_MIN, Tracable::DEFAULT_T_MAX));
    ray = Ray(vec3(2, -2, 2), vec3(-1.5, 1.5, -1));
    CHECK(box.intersect(ray, Tracable::DEFAULT_T_MIN, Tracable::DEFAULT_T_MAX));
    ray = Ray(vec3(0, 0, 0), vec3(1, 1, 1));
    CHECK(box.intersect(ray, Tracable::DEFAULT_T_MIN, Tracable::DEFAULT_T_MAX));
    ray = Ray(vec3(2, 2, 0), vec3(-1, 0, 0));
    CHECK(!box.intersect(ray, Tracable::DEFAULT_T_MIN, Tracable::DEFAULT_T_MAX));
    
    box = BBox(vec3(-1, -1, -1), vec3(1, 1, 1), Transformation (
        vec3(1, 0, 0), M_PI_4, vec3(1, 2, 3)
    ));
    ray = Ray(vec3(3, 2, 4.2), vec3(-1, 0, 0));
    CHECK(box.intersect(ray, Tracable::DEFAULT_T_MIN, Tracable::DEFAULT_T_MAX));
    ray = Ray(vec3(1, 4, 3), vec3(0, -1, 0));
    CHECK(box.intersect(ray, Tracable::DEFAULT_T_MIN, Tracable::DEFAULT_T_MAX));
    ray = Ray(vec3(1, 2, 4), vec3(-1, 2, 0));
    CHECK(box.intersect(ray, Tracable::DEFAULT_T_MIN, Tracable::DEFAULT_T_MAX));
    ray = Ray(vec3(1, 2, 5), vec3(-1, 2, 0));
    CHECK(!box.intersect(ray, Tracable::DEFAULT_T_MIN, Tracable::DEFAULT_T_MAX));

    // for(int i = 0; i < 10000000; i++) {
    //     box = BBox (
    //         vec3(Random::random(-1000, 1000), Random::random(-1000, 1000), Random::random(-1000, 1000)),
    //         vec3(Random::random(-1000, 1000), Random::random(-1000, 1000), Random::random(-1000, 1000))
    //     );
    //     ray = Ray (
    //         vec3(Random::random(-1000, 1000), Random::random(-1000, 1000), Random::random(-1000, 1000)),
    //         Random::randomDirection()
    //     );
    //     box.intersect(ray, TracableObject::DEFAULT_T_MIN, TracableObject::DEFAULT_T_MAX);
    // }
}