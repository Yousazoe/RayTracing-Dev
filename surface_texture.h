#ifndef RAYTRACING_DEV_SURFACE_TEXTURE_H
#define RAYTRACING_DEV_SURFACE_TEXTURE_H

#include "texture.h"

class image_texture : public texture {
public:
    image_texture() {}
    image_texture(unsigned char *pixels, int A, int B)
            : data(pixels), nx(A), ny(B) {}

    ~image_texture() {
        delete data;
    }

    virtual vec3 value(double u, double v, const vec3& p) const {
        // If we have no texture data, then always emit cyan (as a debugging aid).
        if (data == nullptr)
            return vec3(0,1,1);

        auto i = static_cast<int>((u) * nx);
        auto j = static_cast<int>((1 - v) * ny - 0.001);

        if (i < 0) i = 0;
        if (j < 0) j = 0;
        if (i > nx-1) i = nx - 1;
        if (j > ny-1) j = ny - 1;

        auto r = static_cast<int>(data[3 * i + 3 * nx * j + 0]) / 255.0;
        auto g = static_cast<int>(data[3 * i + 3 * nx * j + 1]) / 255.0;
        auto b = static_cast<int>(data[3 * i + 3 * nx * j + 2]) / 255.0;

        return vec3(r, g, b);
    }

public:
    unsigned char *data;
    int nx, ny;
};

#endif //RAYTRACING_DEV_SURFACE_TEXTURE_H