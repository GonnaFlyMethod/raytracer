#include "texture.h"
#include "common_math.h"

Color SolidColor::value(double u, double v, const Point3 &p) const {
    return this->color_value;
}

Color CheckerTexture::value(double u, double v, const Point3 &p) const {
    int x = static_cast<int>(std::floor(p.x() * this->inv_scale));
    int y = static_cast<int>(std::floor(p.y() * this->inv_scale));
    int z = static_cast<int>(std::floor(p.z() * this->inv_scale));

    bool is_even = (x + y + z) % 2 == 0;

    return is_even ? this->even->value(u, v, p) : this->odd->value(u, v, p);
}

ImageTexture::ImageTexture(std::string filename): image(filename){}

Color ImageTexture::value(double u, double v, const Point3 &p) const {
    if(this->image.get_image_height() <= 0) return {0.0f, 1.0f, 1.0f} /* Cyan */;

    u = clamp(u, 0.0f, 1.0f);
    v = 1.0f - clamp(v, 0.0f, 1.0f);  // Flip V to image coordinates

    int i = static_cast<int>(this->image.get_image_width() * u);
    int j = static_cast<int>(this->image.get_image_height() * v);

    auto pixel_data = this->image.get_pixel_data(i,j);

    double color_intensity = 1.0f / 255.0f;
    return {color_intensity * pixel_data[0],
            color_intensity * pixel_data[1],
            color_intensity * pixel_data[2]};
}

PerlinTexture::PerlinTexture(double scaler): frequency_scaler(scaler){};

Color PerlinTexture::value(double u, double v, const Point3 &p) const {
    return Color(1.0f,1.0f,1.0f) * this->perlin_noise.noise(this->frequency_scaler * p);
}
