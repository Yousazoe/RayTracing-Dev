#ifndef RAYTRACING_DEV_TEXTURE_H
#define RAYTRACING_DEV_TEXTURE_H

#include "perlin.h"
#include "rtweekend.h"

class texture {
public:
    virtual vec3 value(double u, double v, const vec3& p) const = 0;
};

class constant_texture : public texture {
public:
    constant_texture() {}
    constant_texture(vec3 c) : color(c) {}

    virtual vec3 value(double u, double v, const vec3& p) const {
        return color;
    }

public:
    vec3 color;
};

class checker_texture : public texture {
public:
    checker_texture() {}
    checker_texture(shared_ptr<texture> t0, shared_ptr<texture> t1) : odd(t0), even(t1) {}

    virtual vec3 value(double u, double v, const vec3& p) const {
        auto sines = sin(10 * p.x()) * sin(10 * p.y()) * sin(10 * p.z());
        if (sines < 0)
            return odd->value(u, v, p);
        else
            return even->value(u, v, p);
    }

public:
    shared_ptr<texture> odd;
    shared_ptr<texture> even;
};


class noise_texture : public texture {
public:
    noise_texture() {}
    noise_texture(double sc) : scale(sc) {}

    virtual vec3 value(double u, double v, const vec3& p) const {
        return vec3(1, 1, 1) * 0.5 * (1 + sin(scale * p.z() + 10 * noise.turb(p)));
    }

public:
    perlin noise;
    double scale;
};

#endif //RAYTRACING_DEV_TEXTURE_H