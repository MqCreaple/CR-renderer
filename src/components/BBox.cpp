#include "components/BBox.h"

BBox::BBox(const glm::vec3& bound1, const glm::vec3& bound2, const Transformation& transformation): ThreeDObject(transformation) {
    if(bound1.x < bound2.x) {
        bounds[0].x = bound1.x;
        bounds[1].x = bound2.x;
    } else {
        bounds[0].x = bound2.x;
        bounds[1].x = bound1.x;
    }
    if(bound1.y < bound2.y) {
        bounds[0].y = bound1.y;
        bounds[1].y = bound2.y;
    } else {
        bounds[0].y = bound2.y;
        bounds[1].y = bound1.y;
    }
    if(bound1.z < bound2.z) {
        bounds[0].z = bound1.z;
        bounds[1].z = bound2.z;
    } else {
        bounds[0].z = bound2.z;
        bounds[1].z = bound1.z;
    }
}

BBox::BBox(const std::vector<glm::vec3>& vertices, const Transformation& transformation): ThreeDObject(transformation) {
    bounds[0] = glm::vec3(INFINITY, INFINITY, INFINITY);
    bounds[1] = glm::vec3(-INFINITY, -INFINITY, -INFINITY);
    for(int i = 0; i < vertices.size(); i++) {
        bounds[0].x = (vertices[i].x < bounds[0].x)? vertices[i].x: bounds[0].x;
        bounds[0].y = (vertices[i].y < bounds[0].y)? vertices[i].y: bounds[0].y;
        bounds[0].z = (vertices[i].z < bounds[0].z)? vertices[i].z: bounds[0].z;
        bounds[1].x = (vertices[i].x > bounds[1].x)? vertices[i].x: bounds[1].x;
        bounds[1].y = (vertices[i].y > bounds[1].y)? vertices[i].y: bounds[1].y;
        bounds[1].z = (vertices[i].z > bounds[1].z)? vertices[i].z: bounds[1].z;
    }
}

bool BBox::intersect(const Ray& ray, float tMin, float tMax) const {
    glm::vec3 rayLocalPos = toLocalCoord(ray.position());
    glm::vec3 rayLocalDir = ray.direction() * transformation.getRotation();
    glm::vec3 invDir = 1.0f / rayLocalDir;
    
    float tm = (bounds[invDir.x < 0].x - rayLocalPos.x) * invDir.x;
    float tM = (bounds[invDir.x >= 0].x - rayLocalPos.x) * invDir.x;

    float tym = (bounds[invDir.y < 0].y - rayLocalPos.y) * invDir.y;
    float tyM = (bounds[invDir.y >= 0].y - rayLocalPos.y) * invDir.y;
    if(tyM < tm || tym > tM) {
        return false;
    }
    tm = (tym > tm)? tym: tm;
    tM = (tyM < tM)? tyM: tM;

    float tzm = (bounds[invDir.z < 0].z - rayLocalPos.z) * invDir.z;
    float tzM = (bounds[invDir.z >= 0].z - rayLocalPos.z) * invDir.z;
    if(tzM < tm || tzm > tM) {
        return false;
    }
    tm = (tzm > tm)? tzm: tm;
    tM = (tzM < tM)? tzM: tM;
    return ((tm > tMin && tm < tMax) || (tm <= tMin && tM > tMin && tM < tMax));
}

/* The old method to calculate intersection is not effecient enough
// bool BBox::intersect(const Ray& ray, float tMin, float tMax) const {
//     Ray rayLocal = Ray(toLocalCoord(ray.position()), ray.direction() * transformation.getRotation());
//     glm::vec3 invDir = 1.0f / rayLocal.direction(), tmp;

//     float tx1 = (bounds[0].x - rayLocal.position().x) * invDir.x;
//     tmp = rayLocal.at(tx1);
//     if(tmp.y >= bounds[0].y && tmp.y <= bounds[1].y && tmp.z >= bounds[0].z && tmp.z <= bounds[1].z) {
//         return true;
//     }
//     float tx2 = (bounds[1].x - rayLocal.position().x) * invDir.x;
//     tmp = rayLocal.at(tx2);
//     if(tmp.y >= bounds[0].y && tmp.y <= bounds[1].y && tmp.z >= bounds[0].z && tmp.z <= bounds[1].z) {
//         return true;
//     }

//     float ty1 = (bounds[0].y - rayLocal.position().y) * invDir.y;
//     tmp = rayLocal.at(ty1);
//     if(tmp.x >= bounds[0].x && tmp.x <= bounds[1].x && tmp.z >= bounds[0].z && tmp.z <= bounds[1].z) {
//         return true;
//     }
//     float ty2 = (bounds[1].y - rayLocal.position().y) * invDir.y;
//     tmp = rayLocal.at(ty2);
//     if(tmp.x >= bounds[0].x && tmp.x <= bounds[1].x && tmp.z >= bounds[0].z && tmp.z <= bounds[1].z) {
//         return true;
//     }
    
//     float tz1 = (bounds[0].z - rayLocal.position().z) * invDir.z;
//     tmp = rayLocal.at(tz1);
//     if(tmp.x >= bounds[0].x && tmp.x <= bounds[1].x && tmp.y >= bounds[0].y && tmp.y <= bounds[1].y) {
//         return true;
//     }
//     float tz2 = (bounds[1].z - rayLocal.position().z) * invDir.z;
//     tmp = rayLocal.at(tz2);
//     return (tmp.x >= bounds[0].x && tmp.x <= bounds[1].x && tmp.y >= bounds[0].y && tmp.y <= bounds[1].y);
// }
*/