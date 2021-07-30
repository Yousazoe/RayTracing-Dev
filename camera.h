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
            double vfov, double aspect, double aperture, double focus_dist, double t0 = 0, double t1 = 0) { // top to bottom, in degress
        origin = lookfrom;
        lens_radius = aperture / 2;

        auto theta = degree_to_radians(vfov);
        auto half_height = tan(theta / 2);
        auto half_width = aspect * half_height;
        time0 = t0;
        time1 = t1;
        w = unit_vector(lookfrom - lookat);
        u = unit_vector(cross(vup, w));
        v = cross(w, u);

        lower_left_corner = origin
                          - half_width * focus_dist * u
                          - half_height * focus_dist * v
                          - focus_dist * w;

        horizontal = 2 * half_width * focus_dist * u;
        vertical = 2 * half_height * focus_dist * v;
    }

    ray get_ray(double s, double t) {
        vec3 rd = lens_radius * random_in_unit_disk();
        vec3 offset = u * rd.x() + v * rd.y();

        return ray(
                origin + offset,
                lower_left_corner + s * horizontal + t * vertical - origin - offset,
                random_double(time0, time1)
                );
    }

public:
    vec3 origin;
    vec3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
    vec3 u, v, w;
    double lens_radius;
    double time0, time1;  // shutter open/close times
};

#endif //RAYTRACING_DEV_CAMERA_H
