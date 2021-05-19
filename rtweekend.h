#ifndef RAYTRACING_DEV_RTWEEKEND_H
#define RAYTRACING_DEV_RTWEEKEND_H

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>

// Usings
using std::shared_ptr;
using std::make_shared;


// Constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;


// Utility Function
inline double degree_to_radians(double degree) {
    return degree * pi / 180;
}

inline double ffmin(double a,double b){
    return a <= b ? a : b;
}

inline double ffmax(double a,double b){
    return a >= b ? a : b;
}

inline double random_double() {
    // Returns a random real in [0,1)
    return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min,double max) {
    // Returns a random real in [min,max)
    return min + (max - min) * random_double();
}

inline double clamp(double x,double min,double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

// Common Headers
#include "ray.h"
#include "vec3.h"

#endif //RAYTRACING_DEV_RTWEEKEND_H
