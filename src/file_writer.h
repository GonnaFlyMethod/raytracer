#pragma once

#include <map>

#include "hittable_list.h"

void write_colors_into_file(
        std::map<size_t, std::vector<Color>>& final_result,
        int samples_per_pixel, int image_width, int image_height);
