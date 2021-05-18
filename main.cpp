#include "ray.h"

#include <iostream>

/*
 *  Function: hit_sphere
 *  Input:
 *      center: sphere center point
 *      radius: sphere radius
 *      ray: hit ray
 *
 *  Output:
 *      delta: hit position time (ray.t)
 *
 *  Math Derivation:
 *      (p(t) - c)(p(t) - c) = R * R -> a t^2 + b t + c = 0
 *      vec(b) * vec(b) t^2 + 2vec(b) * vec(a - c) t + vec(a - c) * vec(a - c) - R * R = 0
 *      a = vec(b) * vec(b)
 *      b = 2vec(b) * vec(a - c)
 *      c = vec(a - c) * vec(a - c) - R * R
 *
 *      delta = b^2 - 4ac
 *      delta > 0 -> root = 2; delta = 0 -> root = 1; delta < 0 -> root = 0
 */
double hit_sphere(const vec3& center,double radius,const ray& r) {
    vec3 oc = r.origin() - center;
    auto a = dot(r.direction(),r.direction());
    auto b = 2.0 * dot(oc,r.direction());
    auto c = dot(oc,oc) - radius * radius;
    auto discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        return -1.0;
    } else {
        return (-b - std::sqrt(discriminant)) / (2.0 * a);
    }
}

/*
 *  Function: ray_color
 *  Input:
 *      ray: render ray with color
 *
 *  Output:
 *      color: lerp color br RGB
 */

vec3 ray_color(const ray& r) {

    //The root ray hit sphere
    auto t = hit_sphere(vec3(0,0,-1),0.5,r);

    if (t > 0.0) {
        vec3 N = unit_vector(vec3(r.at(t) - vec3(0,0,-1)));
        return 0.5 * vec3(N.x() + 1,N.y() + 1,N.z() + 1);
    }

    vec3 unit_direction = unit_vector(r.direction());
    t = 0.5 * (unit_direction.y() + 1.0);

    return (1.0 - t) * vec3(1.0,1.0,1.0) + t * vec3(0.5,0.7,1.0);
}



int main() {
    const int image_width = 200;
    const int image_height = 100;

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    vec3 lower_left_corner(-2.0,-1.0,-1.0);
    vec3 horizontal(4.0,0.0,0.0);
    vec3 vertical(0.0,2.0,0.0);
    vec3 origin(0.0,0.0,0.0);

    for (int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            auto u = double(i) / image_width;
            auto v = double(j) /image_height;

            ray r(origin,lower_left_corner + u * horizontal + v * vertical);
            vec3 color = ray_color(r);
            color.write_color(std::cout);
        }
    }

    std::cerr << "\nDone.\n";
}