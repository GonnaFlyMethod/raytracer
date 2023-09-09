#pragma once

#include <memory>

#include "vec3.h"
#include "image_wrapper.h"
#include "perlin.h"

// TODO: refactor the structure of inheritance for textures

class Texture {
public:
    virtual ~Texture() = default;

    virtual Color value(double u, double v, const Point3& p) const = 0;
};

class SolidColor: public Texture{
private:
    Color color_value;

public:
    SolidColor(Color& c): color_value(c){};
    SolidColor(double red, double green, double blue): color_value(Color(red, green, blue)) {};

    virtual Color value(double u, double v, const Point3& p) const override;
};

class CheckerTexture: public Texture{
private:
    double inv_scale;
    std::shared_ptr<Texture> even, odd;

public:
    CheckerTexture(double scale, Color c1, Color c2)
        : inv_scale(1.0f / scale),
        even(std::make_shared<SolidColor>(c1)),
        odd(std::make_shared<SolidColor>(c2)){};

    Color value(double u, double v, const Point3& p) const override;
};


class ImageTexture: public Texture{
private:
    ImageWrapper image;

public:
    ImageTexture(std::string filename);

    Color value(double u, double v, const Point3& p) const override;
};

class PerlinTexture: public Texture{
private:
    Perlin perlin_noise;

public:
    Color value(double u, double v, const Point3& p) const override;
};