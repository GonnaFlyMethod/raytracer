#pragma once

#define STB_IMAGE_IMPLEMENTATION
#define STBI_FAILURE_USERMSG

#include "external/stb_image.h"

#include <string>

class ImageLoader {
private:
    unsigned char *data;
    const int bytes_per_pixel = 3;
    int image_width, image_height;
    int bytes_per_scanline;
public:
    ImageLoader(): data(nullptr);
    ImageLoader(std::string& path_to_file);
    ~ImageLoader();

    bool load(std::string& filename);

    int get_image_width();
    int get_image_height();

    const unsigned char* get_data(int x, int y) const;
};

