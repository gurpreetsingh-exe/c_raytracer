#pragma once

#ifndef RAY_H
#define RAY_H

#include "vec3.h"

typedef struct {
    Vec3 origin, dir;
} Ray;

Ray* make_ray(const Vec3 origin, const Vec3 dir);
Vec3 rayAt(Ray* ray, float t);

#endif // RAY_H
