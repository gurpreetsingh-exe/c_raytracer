#include "vec3.h"

#define MAX(a) a < 0 ? 0 : a

Vec3 make_vec3(float x, float y, float z) {
    Vec3 v = {
        .x = x,
        .y = y,
        .z = z,
    };
    return v;
}

int formatVec(FILE *in, Vec3 vec) {
    int result = fprintf(in, "%d %d %d\n",
        MAX((int)(vec.x * 255)),
        MAX((int)(vec.y * 255)),
        MAX((int)(vec.z * 255)));

    return result;
}

inline Vec3 vec3Add(Vec3 v1, Vec3 v2) {
    return make_vec3(
        v1.x + v2.x,
        v1.y + v2.y,
        v1.z + v2.z
    );
}

inline Vec3 vec3Sub(Vec3 v1, Vec3 v2) {
    return make_vec3(
        v1.x - v2.x,
        v1.y - v2.y,
        v1.z - v2.z
    );
}

inline Vec3 vec3Mul(Vec3 v1, Vec3 v2) {
    return make_vec3(
        v1.x * v2.x,
        v1.y * v2.y,
        v1.z * v2.z
    );
}

inline Vec3 vec3Scale(Vec3 v1, float f) {
    return make_vec3(
        v1.x * f,
        v1.y * f,
        v1.z * f
    );
}

inline Vec3 vec3Div(Vec3 v1, Vec3 v2) {
    return make_vec3(
        v1.x / v2.x,
        v1.y / v2.y,
        v1.z / v2.z
    );
}

inline float length(Vec3 v) {
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

inline float dot(Vec3 v1, Vec3 v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

inline Vec3 cross(Vec3 v1, Vec3 v2) {
    return make_vec3(
        (v1.y * v2.z) - (v2.y * v1.z),
        (v1.z * v2.x) - (v2.z * v1.x),
        (v1.x * v2.y) - (v2.x * v1.y)
    );
}

inline Vec3 normalize(Vec3 v) {
    float f = length(v);
    Vec3 v2 = make_vec3(f, f, f);
    return vec3Div(v, v2);
}
