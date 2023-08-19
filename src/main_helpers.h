#pragma once

#include <map>

#include "hittable_list.h"

void add_objects_to_world(HittableList& world);

void write_colors_into_file(
        std::map<size_t, std::vector<Color>>& final_result,
        int samples_per_pixel, int image_width, int image_height);
