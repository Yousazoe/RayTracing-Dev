#ifndef RAYTRACING_DEV_ONB_H
#define RAYTRACING_DEV_ONB_H

#include "rtweekend.h"

inline vec3 random_cosine_direction() {
    auto r1 = random_double();
    auto r2 = random_double();
    auto z = sqrt(1 - r2);

    auto phi = 2 * pi * r1;
    auto x = cos(phi) * sqrt(r2);
    auto y = sin(phi) * sqrt(r2);

    return vec3(x, y, z);
}

class onb {
public:
    onb() {}

    inline vec3 operator[](int i) const { return axis[i]; }

    vec3 u() const { return axis[0]; }
    vec3 v() const { return axis[1]; }
    vec3 w() const { return axis[2]; }

    vec3 local(double a, double b, double c) const {
        return a*u() + b*v() + c*w();
    }

    vec3 local(const vec3& a) const {
        return a.x()*u() + a.y()*v() + a.z()*w();
    }

    void build_from_w(const vec3&);

public:
    vec3 axis[3];
};


void onb::build_from_w(const vec3& n) {
    axis[2] = unit_vector(n);
    vec3 a = (fabs(w().x()) > 0.9) ? vec3(0,1,0) : vec3(1,0,0);
    axis[1] = unit_vector(cross(w(), a));
    axis[0] = cross(w(), v());
}

#endif //RAYTRACING_DEV_ONB_H
