 #pragma once

#include "components/ThreeDObject.h"
#include "components/TracableObject.h"
#include "components/BBox.h"
#include <vector>
#include <string>
#include <memory>

/**
 * @brief A single surface on the triangle mesh.
 */
class TriangleSurface: public TracableObject {
public:
    /**
     * @brief Construct a surface with vertex array reference and indices
     * @param vertices reference of vertex array
     * @param indices indices of three vertices in the array
     * @param transformation transformation performed on the surface
     */
    TriangleSurface (
        const std::vector<glm::vec3>& vertices,
        const glm::ivec3& indices,
        const Transformation& transformation = Transformation::DEFAULT
    );
    /**
     * @brief Get the surface's normal vector in world coordinate (with transformation).
     * @return glm::vec3 normal vector in world coordinate
     */
    glm::vec3 normal() const;
    /**
     * @brief Get the surface's normal vector in local coordinate (without transformation).
     * @return glm::vec3 normal vector in local coordinate
     */
    glm::vec3 localNormal() const;
    HitResult intersect(const Ray& ray, float tMin = DEFAULT_T_MIN, float tMax = DEFAULT_T_MAX) const override;
private:
    // ? shared, unique, or default pointer?
    std::shared_ptr<const std::vector<glm::vec3>> vertices;
    int v0, v1, v2;
};

/**
 * @brief Defines object composed of triangle surfaces
 */
class TriangleMeshObject: public TracableObject {
public:
    /**
     * @brief Construct a new Triangle Mesh Object
     * @param v vertices array
     * @param s surface index array
     */
    TriangleMeshObject(std::vector<glm::vec3>& v, std::vector<glm::i32vec3>& s, const Transformation& t = Transformation::DEFAULT);
    /**
     * @brief Construct a new Triangle Mesh Object from an obj file
     * @param file file name
     */
    TriangleMeshObject(const std::string& file, const Transformation& t = Transformation::DEFAULT);
    /**
     * @brief load object from an obj file
     * @param file filename
     */
    void loadFromFile(const std::string& file, const Transformation& t = Transformation::DEFAULT);

    /**
     * @brief Get the Surface object by index
     * @param index index of surface in @c surfaces array
     * @return Surface surface object
     */
    TriangleSurface getSurface(int index) const;

    HitResult intersect(const Ray& ray, float tMin = DEFAULT_T_MIN, float tMax = DEFAULT_T_MAX) const override;
private:
    std::vector<glm::vec3>& vertices;
    std::vector<glm::i32vec3>& surfaces;
    BBox box;
};