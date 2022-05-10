#include <malloc.h>
#include "ray.h"

Ray* make_ray(const Vec3 origin, const Vec3 dir) {
    Ray* ray = malloc(sizeof(ray));
    ray->origin = origin;
    ray->dir = dir;

    return ray;
}

inline Vec3 rayAt(Ray* ray, float t) {
    return vec3Add(ray->origin, vec3Scale(ray->dir, t));
}
