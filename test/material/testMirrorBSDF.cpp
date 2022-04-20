#include "TestInclude.h"
#include "material/MirrorBSDF.h"

int main() {
    MirrorBSDF m(0.8);
    glm::vec3 wo(1, 2, 3);
    wo = glm::normalize(wo);
    glm::vec3 wi;
    Spectrum f = m.sample(wo, wi);
    CHECK_EPSILON_EQU(f, 0.8, 2e-7f);
    CHECK_EPSILON_EQU(wi, glm::normalize(glm::vec3(-1, -2, 3)), 2e-7f);
}