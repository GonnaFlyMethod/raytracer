#include "texture.h"

Color SolidColor::value(double u, double v, const Point3 &p) const {
    return this->color_value;
}