#pragma once

#include "common_math/random.h"
#include "hittable.h"
#include "common_math/other.h"
#include "texture.h"

class Material{
public:
    virtual bool scatter(
            const CommonMath::Ray& r_in, const hit_record & rec, CommonMath::Color& attenuation, CommonMath::Ray& scattered) const = 0;
};

class Lambertian: public Material{
private:
    std::shared_ptr<Texture> albedo;
public:
    Lambertian(const std::shared_ptr<Texture>& c): albedo(c){};
    Lambertian(CommonMath::Color c): albedo(std::make_shared<SolidColor>(c)){};

    virtual bool scatter(
            const CommonMath::Ray& r_in, const hit_record& rec, CommonMath::Color& attenuation, CommonMath::Ray& scattered) const override;
};

class Metal: public Material{
private:
    CommonMath::Color albedo;
    double fuzz;
public:
    Metal(const CommonMath::Color& a, double f): albedo(a), fuzz(CommonMath::clamp(f, -1.0f, 1.0f)){}

    virtual bool scatter(
            const CommonMath::Ray& r_in, const hit_record & rec, CommonMath::Color& attenuation, CommonMath::Ray& scattered) const override;
};


class Dielectric: public Material{
private:
    // TODO: Add dynamic albedo

    double index_of_refraction;

    static double reflectance(double cosine, double refraction_index);

public:
    Dielectric(double ior): index_of_refraction(ior){}

    virtual bool scatter(
            const CommonMath::Ray& r_in, const hit_record & rec, CommonMath::Color& attenuation, CommonMath::Ray& scattered) const override;
};
