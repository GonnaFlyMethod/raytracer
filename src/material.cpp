#include "material.h"

bool Lambertian::scatter(const Ray &r_in, const hit_record &rec, Color &attenuation, Ray &scattered) const {
    Vec3 scatter_dir = rec.normal + random_unit_vector();

    if (scatter_dir.near_zero()){
        scatter_dir = rec.normal;
    }

    scattered = Ray(rec.p, scatter_dir);
    attenuation = this->albedo;
    return true;
}

bool Metal::scatter(const Ray &r_in, const hit_record &rec, Color &attenuation, Ray &scattered) const {

    Vec3 scatter_dir = reflect(unit_vector(r_in.GetDirection()), rec.normal);

    scattered = Ray(rec.p, scatter_dir + random_unit_vector() * fuzz);
    attenuation = this->albedo;
    return dot(rec.normal, scattered.GetDirection()) > 0.0f;
}

double Dielectric::reflectance(double cosine, double refraction_index) {
    double r0 = (1 - refraction_index) / (1 + refraction_index);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow((1 - cosine), 5);
}

bool Dielectric::scatter(const Ray &r_in, const hit_record &rec, Color &attenuation, Ray &scattered) const {
    attenuation = Color(1.0f, 1.0f, 1.0f);

    double refraction_ratio = rec.front_face ? (1.0/ this->index_of_refraction): index_of_refraction;
    Vec3 unit_direction = unit_vector(r_in.GetDirection());

    Vec3 refracted_ray = refract(unit_direction, rec.normal, refraction_ratio);

    double cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0f);
    double sin_theta = sqrt(1 - cos_theta * cos_theta);

    bool cannot_refract = refraction_ratio * sin_theta > 1.0f;

    Vec3 direction;

    if (cannot_refract || this->reflectance(cos_theta, refraction_ratio) > random_double()){
        direction = reflect(unit_direction, rec.normal);
    }else{
        direction = refract(unit_direction, rec.normal, refraction_ratio);
    }

    scattered = Ray(rec.p, direction);

    return true;
}