#pragma once

#include <iostream>
#include <ios>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

// output

template<typename T>
inline void outputSingle(T t) {}

template<>
inline void outputSingle(int v) {
    std::cout << v;
}

template<>
inline void outputSingle(float f) {
    std::cout << f;
}

template<>
inline void outputSingle(double d) {
    std::cout << d;
}

template<>
inline void outputSingle(const char* s) {
    std::cout << s;
}

template<>
inline void outputSingle(glm::vec3 v) {
    std::cout << "[" << v.x << ", " << v.y << ", " << v.z << "]";
}

template<>
inline void outputSingle(glm::quat q) {
    std::cout.setf(std::ios::showpos);
    std::cout << q.w << q.x << "i" << q.y << "j" << q.z << "k";
    std::cout.unsetf(std::ios::showpos);
}

template<typename T>
void output(T t) {
    outputSingle(t);
}

template<typename T, typename...U>
void output(T t, U...args) {
    outputSingle(t);
    output(args...);
}

// epsilon equal

inline bool testEpsilonNotEqual(const glm::vec3& v1, const glm::vec3& v2, float epsilon) {
    return (abs(v1.x - v2.x) >= epsilon) ||
           (abs(v1.y - v2.y) >= epsilon) ||
           (abs(v1.z - v2.z) >= epsilon);
}

inline bool testEpsilonNotEqual(const glm::quat& q1, const glm::quat& q2, float epsilon) {
    return (abs(q1.w - q2.w) >= epsilon) ||
           (abs(q1.x - q2.x) >= epsilon) ||
           (abs(q1.y - q2.y) >= epsilon) ||
           (abs(q1.z - q2.z) >= epsilon);
}

inline bool testEpsilonNotEqual(float f1, float f2, float epsilon) {
    return abs(f1 - f2) >= epsilon;
}

// checking

#define CHECK(exp) if(!(exp)) { \
    output("Error while checking `"#exp"`\n"); \
    output("Line: ", __LINE__, ", File: \"", __FILE__, "\""); return 1; }
#define CHECK_EQU(exp1, exp2) if(exp1 != exp2) { \
    output("ERROR: Expression `"#exp1"` and `"#exp2"` are not equal!\n"); \
    output("LHS: ", exp1, "; RHS: ", exp2, "\n"); \
    output("Line: ", __LINE__, ", File: \"", __FILE__, "\""); return 1; }
#define CHECK_EPSILON_EQU(exp1, exp2, epsilon) if(testEpsilonNotEqual(exp1, exp2, epsilon)) { \
    output("ERROR: Expression `"#exp1"` and `"#exp2"` are not epsilon equal!\n"); \
    output("LHS: ", exp1, "; RHS: ", exp2, "; epsilon: ", epsilon, "\n"); \
    output("Line: ", __LINE__, ", File: \"", __FILE__, "\""); return 1; }
