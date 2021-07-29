#ifndef RAYTRACING_DEV_CAMERA_H
#define RAYTRACING_DEV_CAMERA_H

#include "rtweekend.h"

class camera {
public:
    camera() {
        lower_left_corner = vec3(-2.0,-1.0,-1.0);
        horizontal = vec3(4.0,0.0,0.0);
        vertical = vec3(0.0,2.0,0.0);
        origin = vec3(0.0,0.0,0.0);
    }

    camera(vec3 lookfrom, vec3 lookat, vec3 vup,
            double vfov, double aspect) { // top to bottom, in degress
        origin = lookfrom;

        auto theta = degree_to_radians(vfov);
        auto half_height = tan(theta / 2);
        auto half_width = aspect * half_height;
        vec3 w = unit_vector(lookfrom - lookat);
        vec3 u = unit_vector(cross(vup, w));
        vec3 v = cross(w, u);

        lower_left_corner = origin - half_width * u - half_height * v - w;

        horizontal = 2 * half_width * u;
        vertical = 2 * half_height * v;
    }

    ray get_ray(double u,double v) {
        return ray(origin,lower_left_corner + u * horizontal + v * vertical - origin);
    }

public:
    vec3 origin;
    vec3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
};

#endif //RAYTRACING_DEV_CAMERA_H
