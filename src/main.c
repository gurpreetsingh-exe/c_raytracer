#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vec3.h"
#include "ray.h"
#include "hitinfo.h"
#include "config.h"

#define MIN(a, b) a < b ? a : b

bool ray_sphere_intersection(Ray* ray, Vec3 center, float radius, HitInfo* r_hitInfo) {
    Vec3 v = vec3Sub(ray->origin, center);
    float b = dot(v, ray->dir);
    float c = b * b - (dot(v, v) - radius * radius);
    float dist = -b + sqrtf(c);
    bool intersect = false;
    if (dist < 0.0) {
        r_hitInfo->dist = dist;
        r_hitInfo->normal = normalize(
            vec3Sub(
                rayAt(ray, dist), center));

        intersect = true;
    }
    return intersect;
}

bool ray_tri_intersection(Ray* ray, Vec3 v0, Vec3 v1, Vec3 v2, HitInfo* r_hitInfo) {
    const float EPSILON = 0.00000001;
    Vec3 edge1 = vec3Sub(v1, v0);
    Vec3 edge2 = vec3Sub(v2, v0);

    Vec3 h = cross(ray->dir, edge2);
    float a = dot(edge1, h);
    if (a > -EPSILON && a < EPSILON) {
        return false;
    }

    float f = 1.0 / a;
    Vec3 s = vec3Sub(ray->origin, v0);
    float u = f * dot(s, h);
    if (u < 0.0 || u > 1.0) {
        return false;
    }

    Vec3 q = cross(s, edge1);
    float v = f * dot(ray->dir, q);
    if (v < 0.0 || u + v > 1.0) {
        return false;
    }

    r_hitInfo->dist = f * dot(edge2, q);
    r_hitInfo->normal = vec3Scale(normalize(cross(edge2, edge1)), -1.0);
    return true;
}

bool ray_plane_intersection(Ray* ray, Vec3 v0, Vec3 v1, Vec3 v2, Vec3 v3, HitInfo* r_hitInfo) {
    bool intersection = ray_tri_intersection(ray, v0, v1, v2, r_hitInfo);
    intersection |= ray_tri_intersection(ray, v1, v3, v2, r_hitInfo);
    r_hitInfo->normal = vec3Scale(r_hitInfo->normal, -1);

    return intersection;
}

bool sceneTrace(Ray* ray, HitInfo* r_hitInfo) {
    // back
    bool intersection = ray_plane_intersection(
        ray,
        make_vec3(-1.0, -1.0,  0.0),
        make_vec3(-1.0,  1.0,  0.0),
        make_vec3( 1.0, -1.0,  0.0),
        make_vec3( 1.0,  1.0,  0.0),
        r_hitInfo
    );

    // up
    intersection &= ray_plane_intersection(
        ray,
        make_vec3(-1.0,  1.0,  0.0),
        make_vec3( 1.0,  1.0,  0.0),
        make_vec3(-1.0,  1.0,  1.0),
        make_vec3( 1.0,  1.0,  1.0),
        r_hitInfo
    );

    // down
    intersection &= ray_plane_intersection(
        ray,
        make_vec3(-1.0, -1.0,  0.0),
        make_vec3( 1.0, -1.0,  0.0),
        make_vec3(-1.0, -1.0,  1.0),
        make_vec3( 1.0, -1.0,  1.0),
        r_hitInfo
    );

    // right
    intersection &= ray_plane_intersection(
        ray,
        make_vec3( 1.0, -1.0,  0.0),
        make_vec3( 1.0, -1.0,  1.0),
        make_vec3( 1.0,  1.0,  0.0),
        make_vec3( 1.0,  1.0,  1.0),
        r_hitInfo
    );

    // left
    intersection &= ray_plane_intersection(
        ray,
        make_vec3(-1.0, -1.0,  0.0),
        make_vec3(-1.0, -1.0,  1.0),
        make_vec3(-1.0,  1.0,  0.0),
        make_vec3(-1.0,  1.0,  1.0),
        r_hitInfo
    );

    intersection &= ray_sphere_intersection(ray, make_vec3(0, 0, 0), 0.5, r_hitInfo);
    return intersection;
}

Vec3 getColor(Ray* ray) {
    HitInfo hitInfo = {
        .dist = 1000.0,
        .normal = make_vec3(0, 0, 0),
    };

    sceneTrace(ray, &hitInfo);
    Vec3 lightPos = make_vec3(0.4, 0.6, 1.0);

    if (hitInfo.dist < 1000.0) {
        Vec3 position = rayAt(ray, hitInfo.dist);
        Vec3 lightDir = normalize(vec3Sub(lightPos, position));
        float light = dot(lightDir, hitInfo.normal);
        return make_vec3(light, light, light);
    } else {
        return make_vec3(0, 0, 0);
    }
}

void writeFile(const char *fileName) {
    FILE *in = fopen(fileName, "w");
    if (in == NULL) {
        fputs("File not found\n", stderr);
        exit(1);
    }

    size_t result = fprintf(in, "P3\n%d %d\n255\n", IMG_WIDTH, IMG_HEIGHT);

    if (!result) {
        fputs("Error when writing to file\n", stderr);
        exit(1);
    }

    Ray* ray = malloc(sizeof(Ray));
    for (int j = IMG_HEIGHT; j >= 0; --j) {
        for (int i = 0; i < IMG_WIDTH; ++i) {
            float x = ((float)i / IMG_WIDTH);
            float y = ((float)j / IMG_HEIGHT);
            Vec3 origin = make_vec3(0.0, 0.0, 4.0);
            Vec3 dir = normalize(
                vec3Sub(origin,
                    make_vec3(
                        (x - 0.5) * 2, (y - 0.5) * 2, 1.0)));

            ray->origin = origin;
            ray->dir = dir;

            Vec3 color = getColor(ray);
            result += formatVec(in, color);
        }
    }
    free(ray);
}

int main() {
    writeFile("image.ppm");
}
