#pragma once

#ifndef VEC3_H
#define VEC3_H

#include <math.h>
#include <stdio.h>
#include "config.h"

typedef struct {
    float x, y, z;
} Vec3;

Vec3 make_vec3(float x, float y, float z);
int formatVec(FILE *in, Vec3 vec);
Vec3 vec3Add(Vec3 v1, Vec3 v2);
Vec3 vec3Sub(Vec3 v1, Vec3 v2);
Vec3 vec3Mul(Vec3 v1, Vec3 v2);
Vec3 vec3Scale(Vec3 v1, float f);
Vec3 vec3Div(Vec3 v1, Vec3 v2);
float length(Vec3 v);
float dot(Vec3 v1, Vec3 v2);
Vec3 cross(Vec3 v1, Vec3 v2);
Vec3 normalize(Vec3 v);

#endif // VEC3_H
