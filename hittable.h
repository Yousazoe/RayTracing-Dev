#ifndef RAYTRACING_DEV_HITTABLE_H
#define RAYTRACING_DEV_HITTABLE_H

#include "ray.h"

struct hit_record {
    vec3 p;
    vec3 normal;
    double t;
    bool front_face;

    inline void set_face_normal(const ray& r,const vec3& outwardnormal) {
        front_face = dot(r.direction(),outwardnormal) < 0;
        normal = front_face ? outwardnormal : -outwardnormal;
    }
};

class hittable {
public:
    virtual bool hit(const ray& r,double  t_min,double  t_max,hit_record& rec) const = 0;
};

#endif //RAYTRACING_DEV_HITTABLE_H