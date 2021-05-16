#include "ray.h"

#include <iostream>

bool hit_sphere(const vec3& center,double radius,const ray& r) {
    vec3 oc = r.origin() - center;
    auto a = dot(r.direction(),r.direction());
    auto b = 2.0 * dot(oc,r.direction());
    auto c = dot(oc,oc) - radius * radius;
    auto discriminant = b * b - 4 * a * c;

    return (discriminant > 0);
}

vec3 ray_color(const ray& r) {

    if (hit_sphere(vec3(0,0,-1),0.5,r))
        return vec3(1,0,0);

    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);

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