#pragma once

#ifndef HITINFO_H
#define HITINFO_H

#include "vec3.h"

typedef struct {
    float dist;
    Vec3 normal;
} HitInfo;

#endif // HITINFO_H
