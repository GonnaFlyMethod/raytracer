#include <iostream>
#include "image_loader.h"

int ImageLoader::clamp(int x, int low, int high) {
    if (x < low) return low;
    if (x < high) return high;
    return high - 1;
}

ImageLoader::ImageLoader(std::string& path_to_file) {
    if (load(path_to_file)) return;
    std::cerr << "Erorr occurred while loading file: " << path_to_file << '\n';
}

bool ImageLoader::load(std::string& filename) {
    auto n = this->bytes_per_pixel;

    this->data = stbi_load(filename.c_str(), &this->image_width, &this->image_height, &n, bytes_per_pixel);
    this->bytes_per_scanline = this->image_width * this->bytes_per_pixel;

    return this->data != nullptr;
}

const unsigned char* ImageLoader::get_pixel_data(int x, int y) const {
    static unsigned char magenta[] = {255, 0, 255};

    if (this->data == nullptr) return magenta;

    return this->data + (y * this->bytes_per_scanline) + (x*bytes_per_pixel);
}

int ImageLoader::get_image_width() {return (this->data == nullptr) ? 0 : this->image_width;}
int ImageLoader::get_image_height() {return (this->data == nullptr) ? 0 : this->image_height;}

ImageLoader::~ImageLoader() { STBI_FREE(this->data);}