#ifndef RAYTRACING_DEV_MATERIAL_H
#define RAYTRACING_DEV_MATERIAL_H

#include "ray.h"
#include "hittable.h"

class material {
public:
    virtual bool scatter(
            const ray& r_in,const hit_record& rec,vec3& attenuation,ray& scattered
            ) const = 0;
};

class lambertian : public material {
public:
    lambertian(const vec3& a) : albedo(a) {}

    virtual bool scatter(
            const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered
    ) const {
        vec3 scatter_direction = rec.normal + random_unit_vector();
        scattered = ray(rec.p, scatter_direction, r_in.time());
        attenuation = albedo;
        return true;
    }
public:
    vec3 albedo;
};

class metal : public material {
public:
    metal(const vec3& a,double f) : albedo(a), fuzz(f < 1 ? f : 1) {}

    virtual bool scatter(
            const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered
    ) const {
        vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
        scattered = ray(rec.p, reflected + fuzz * random_in_sphere(), r_in.time());
        attenuation = albedo;
        return (dot(scattered.direction(), rec.normal) > 0);
    }

public:
    vec3 albedo;
    double fuzz;
};

class dielectric : public material {
public:
    dielectric(double ri) : ref_idx(ri) {}

    virtual bool scatter (
            const ray& r_in,const hit_record& rec,vec3& attenuation,ray& scattered
    ) const {
        double etai_over_etat;
        attenuation = vec3(1.0, 1.0, 1.0);

        if (rec.front_face) {
            etai_over_etat = 1 / ref_idx;
        } else {
            etai_over_etat = ref_idx;
        }

        vec3 unit_direction = unit_vector(r_in.direction());
        double cos_theta = ffmin(dot(-unit_direction, rec.normal), 1.0);
        double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

        if (etai_over_etat * sin_theta > 1.0) {
            vec3 reflected = reflect(unit_direction, rec.normal);
            scattered = ray(rec.p, reflected);
            return true;
        }

        vec3 refracted = refract(unit_direction, rec.normal, etai_over_etat);
        scattered = ray(rec.p, refracted, r_in.time());

        return true;
    }
public:
    double ref_idx;
private:
    static double reflectance(double cosine, double ref_idx) {
        auto r0 = (1-ref_idx) / (1+ref_idx);
        r0 = r0*r0;
        return r0 + (1-r0)*pow((1 - cosine),5);
    }
};

#endif //RAYTRACING_DEV_MATERIAL_H
