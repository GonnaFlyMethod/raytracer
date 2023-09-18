#pragma once

#include <memory>

#include "perlin.h"
#include "image_wrapper.h"

// TODO: refactor the structure of inheritance for textures

class Texture {
public:
    virtual ~Texture() = default;

    virtual CommonMath::Color value(double u, double v, const CommonMath::Point3& p) const = 0;
};

class SolidColor: public Texture{
private:
    CommonMath::Color color_value;

public:
    SolidColor(CommonMath::Color& c): color_value(c){};
    SolidColor(double red, double green, double blue): color_value(CommonMath::Color(red, green, blue)) {};

    virtual CommonMath::Color value(double u, double v, const CommonMath::Point3& p) const override;
};

class CheckerTexture: public Texture{
private:
    double inv_scale;
    std::shared_ptr<Texture> even, odd;

public:
    CheckerTexture(double scale, CommonMath::Color c1, CommonMath::Color c2)
        : inv_scale(1.0f / scale),
        even(std::make_shared<SolidColor>(c1)),
        odd(std::make_shared<SolidColor>(c2)){};

    CommonMath::Color value(double u, double v, const CommonMath::Point3& p) const override;
};


class ImageTexture: public Texture{
private:
    ImageWrapper image;

public:
    ImageTexture(std::string filename);

    CommonMath::Color value(double u, double v, const CommonMath::Point3& p) const override;
};

class PerlinTexture: public Texture{
private:
    Perlin perlin_noise;
    double frequency_scaler;

public:
    PerlinTexture();
    PerlinTexture(double frequency_scaler);
    CommonMath::Color value(double u, double v, const CommonMath::Point3& p) const override;
};
