#include "components/TriangleMeshObject.h"

// class: "TriangleSurface" //

TriangleSurface::TriangleSurface(const std::vector<glm::vec3>& vertices, const glm::ivec3& indices, const Transformation& transformation)
    : TracableObject(transformation),
    vertices(std::make_shared<const std::vector<glm::vec3>>(vertices)),
    v0(indices[0]), v1(indices[1]), v2(indices[2]) {}

glm::vec3 TriangleSurface::normal() const {
    return transformation.getRotation() * localNormal();
}

glm::vec3 TriangleSurface::localNormal() const {
    glm::vec3 vert0 = vertices->at(v0);
    return glm::normalize(glm::cross(
        vertices->at(v1) - vert0,
        vertices->at(v2) - vert0
    ));
}

TracableObject::HitResult TriangleSurface::intersect(const Ray& ray, float tMin, float tMax) const {
    // triangle-ray intersection algorithm
    // based on "Fast, Minimum Storage Ray-Triangle Intersection" https://doi.org/10.1080/10867651.1997.10487468
    Ray rayLocal = Ray(toLocalCoord(ray.position()), ray.direction() * transformation.getRotation());
    glm::vec3 vert0 = vertices->at(v0);
    glm::vec3 e1 = vertices->at(v1) - vert0, e2 = vertices->at(v2) - vert0, T = rayLocal.position() - vert0;
    glm::vec3 p = glm::cross(rayLocal.direction(), e2), q = glm::cross(T, e1);
    float de = glm::dot(p, e1);
    float t = glm::dot(q, e2) / de;
    float u = glm::dot(p, T) / de;
    float v = glm::dot(q, rayLocal.direction()) / de;
    if(u < 0 || v < 0 || u + v > 1 || t < tMin || t > tMax) {
        return HitResult();
    }
    return HitResult(ray.at(t), normal(), t);
}

// class: "TriangleMeshObject" //

TriangleMeshObject::TriangleMeshObject(std::vector<glm::vec3>& v, std::vector<glm::i32vec3>& s, const Transformation& t)
    : TracableObject(t), vertices(v), surfaces(s), box(v, t) {}

TriangleSurface TriangleMeshObject::getSurface(int index) const {
    return TriangleSurface(vertices, surfaces[index], transformation);
}

TracableObject::HitResult TriangleMeshObject::intersect(const Ray& ray, float tMin, float tMax) const {
    if(!box.intersect(ray, tMin, tMax)) {
        return HitResult();
    }
    HitResult ans;
    ans.t = INFINITY;
    for(int i = 0; i < surfaces.size(); i++) {
        HitResult result = getSurface(i).intersect(ray, tMin, tMax);
        if(result.valid && result.t < ans.t) {
            ans = result;
        }
    }
    return ans;
}