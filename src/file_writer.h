#pragma once

#include <map>

#include "./common_math/vec3.h"

void write_colors_into_file(
        std::map<size_t, std::vector<CommonMath::Color>>& final_result,
        int samples_per_pixel, int image_width, int image_height);
