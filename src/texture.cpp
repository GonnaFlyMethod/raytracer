#include "texture.h"

Color SolidColor::value(double u, double v, const Point3 &p) const {
    return this->color_value;
}

Color CheckerTexture::value(double u, double v, const Point3 &p) const {
    int x = static_cast<int>(std::floor(p.x() * inv_scale));
    int y = static_cast<int>(std::floor(p.y() * inv_scale));
    int z = static_cast<int>(std::floor(p.z() * inv_scale));

    bool is_even = (x + y + z) % 2 == 0;

    return is_even ? even->value(u, v, p) : odd->value(u, v, p);
}
