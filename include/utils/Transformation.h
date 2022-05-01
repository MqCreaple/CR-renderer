#pragma once

#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

/**
 * @brief 3D congruence transformation.
 * Every congruence transformation is represented by the combination of rotation and translation.
 */
class Transformation {
    friend class ThreeDObject;
public:
    static const Transformation DEFAULT;
    /**
     * @brief Construct an identity transformation.
     * Identity transformation returns the same vector as input
     */
    Transformation();
    /**
     * @brief Construct a transformation from rotation quaternion and translation vector
     * @param q rotation quaternion
     * @param v translation vector
     */
    Transformation(const glm::quat& q, const glm::vec3& v);
    /**
     * @brief Construct a transformation using axis of rotation, angle of rotation, and translation vector
     * @param axis rotation axis
     * @param angle rotation angle
     * @param v translation vector
     */
    Transformation(const glm::vec3& axis, float angle, const glm::vec3& v);
    /**
     * @brief Get the rotation component of the transformation
     * @return glm::quat rotation quaternion
     */
    glm::quat getRotation() const;
    /**
     * @brief Get the translation component of the transformation
     * @return glm::vec3 translation vector
     */
    glm::vec3 getTranslation() const;

    /**
     * @brief Get the inverse transformation
     * @return Transformation inverse transformation
     */
    Transformation inv() const;

    /**
     * @brief perform the transformation to a point
     * @param v input point
     * @return glm::vec3 transformed point
     */
    glm::vec3 transform(const glm::vec3& v) const;
    /**
     * @brief perform the inverse transformation to a point
     * @param v input point
     * @return glm::vec3 inverse transformed point
     */
    glm::vec3 invTransform(const glm::vec3& v) const;

    /**
     * @brief Get the transformation matrix
     * @return glm::mat4 transformation matrix
     */
    glm::mat4 getTransformationMatrix() const;
    /**
     * @brief Get the inverse transformation matrix
     * @return glm::mat4 inverse transformation matrix
     */
    glm::mat4 getInvTransformationMatrix() const;

    /**
     * @brief Get the pure rotation transformation.
     * @param n rotation axis
     * @param angle rotation angle
     * @return Transformation transformation
     */
    static Transformation rotation(const glm::vec3& n, float angle);
    /**
     * @brief Get the pure translation transformation.
     * @param tr translation vector
     * @return Transformation transformation
     */
    static Transformation translation(const glm::vec3& tr);

    /**
     * @brief compose two transformation.
     * Given two transformations, returns the equivalent transformation of performing tansformations in order.
     * @param first first transformation to perform
     * @param second second transformation to perform
     * @return Transformation equivalent composed transformation
     */
    static Transformation compose(const Transformation& first, const Transformation& second);
private:
    glm::quat rotate;
    glm::vec3 translate;
};