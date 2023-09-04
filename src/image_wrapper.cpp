#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_FAILURE_USERMSG

#include "external/stb_image.h"

#include "image_wrapper.h"

int ImageWrapper::clamp(int x, int low, int high) {
    if (x < low) return low;
    if (x < high) return x;
    return high - 1;
}

ImageWrapper::ImageWrapper(std::string filename) {
    if (load("textures/" + filename)) return;
    if (load("../textures/" + filename)) return;
    if (load("../../textures/" + filename)) return;
    if (load("../../../textures/" + filename)) return;
    if (load("../../../../textures/" + filename)) return;
    if (load("../../../../../textures/" + filename)) return;
    if (load("../../../../../../textures/" + filename)) return;

    std::cerr << "Erorr occurred while loading file: " << filename << '\n';
}

bool ImageWrapper::load(std::string path_to_file) {
    auto n = this->bytes_per_pixel;

    this->data = stbi_load(path_to_file.c_str(), &this->image_width, &this->image_height, &n, bytes_per_pixel);
    this->bytes_per_scanline = this->image_width * this->bytes_per_pixel;

    return this->data != nullptr;
}

const unsigned char* ImageWrapper::get_pixel_data(int x, int y) const {
    static unsigned char magenta[] = {255, 0, 255};

    if (this->data == nullptr) return magenta;

    x = this->clamp(x, 0, image_width);
    y = this->clamp(y, 0, image_height);

    return this->data + (y * this->bytes_per_scanline) + (x * bytes_per_pixel);
}

int ImageWrapper::get_image_width() const {return (this->data == nullptr) ? 0 : this->image_width;}
int ImageWrapper::get_image_height() const {return (this->data == nullptr) ? 0 : this->image_height;}

ImageWrapper::~ImageWrapper() { STBI_FREE(this->data);}