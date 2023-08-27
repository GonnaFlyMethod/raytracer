#pragma once

#include "vec3.h"

class Texture {
public:
    virtual ~Texture();

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
