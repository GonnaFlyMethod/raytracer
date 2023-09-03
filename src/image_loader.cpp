#include <iostream>
#include "image_loader.h"

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

int ImageLoader::get_image_width() {return (this->data == nullptr) ? 0 : this->image_width;}
int ImageLoader::get_image_height() {return (this->data == nullptr) ? 0 : this->image_height;}