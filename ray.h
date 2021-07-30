#ifndef RAYTRACING_DEV_RAY_H
#define RAYTRACING_DEV_RAY_H

#include "vec3.h"

class ray {
public:
    ray() {}
    ray(const vec3& origin, const vec3& direction, double time = 0)
        : orig(origin), dir(direction), tm(time){

    }

    vec3 origin() const { return orig; }
    vec3 direction() const { return dir; }
    double time() const { return tm; }

    vec3 at(double t) const {
        return orig + t * dir;
    }

public:
    vec3 orig;
    vec3 dir;
    double tm;
};


#endif //RAYTRACING_DEV_RAY_H
