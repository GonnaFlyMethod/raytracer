#pragma once
#include <string>

class ImageWrapper {
private:
    unsigned char *data;
    const int bytes_per_pixel = 3;
    int image_width, image_height;
    int bytes_per_scanline;

    // Returns value in the range [low, max)
    static int clamp(int x, int low, int max);
public:
    ImageWrapper(): data(nullptr){};
    ImageWrapper(std::string filename);
    ~ImageWrapper();

    bool load(std::string path_to_file);

    int get_image_width() const;
    int get_image_height() const;

    const unsigned char* get_pixel_data(int x, int y) const;
};

