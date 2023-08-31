#include <ctime>
#include <sstream>
#include <iomanip>
#include <map>
#include <fstream>

#include "hittable_list.h"
#include "material.h"
#include "sphere.h"
#include "texture.h"

std::string get_current_datetime(){
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y_%m_%d_%H_%M_%S");
    return oss.str();
}

void write_colors_into_file(
        std::map<size_t, std::vector<Color>>& final_result,
        int samples_per_pixel, int image_width, int image_height){
    std::string filename = "render_" + get_current_datetime() + ".ppm";

    std::ofstream file_handler;

    file_handler.open(filename, std::ios::out | std::ios::binary);

    file_handler << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for(auto& [ core_num, pixels_batch ] :  final_result){
        for (const auto& color : pixels_batch){

            double scale = 1.0 / samples_per_pixel;

            double r = color.x();
            double g = color.y();
            double b = color.z();

            r = sqrt(r * scale);
            g = sqrt(g * scale);
            b = sqrt(b * scale);

            file_handler << static_cast<int>(256 * clamp(r, 0, 0.999)) << ' '
                << static_cast<int>(256 * clamp(g, 0, 0.999)) << ' '
                << static_cast<int>(256 * clamp(b, 0, 0.999)) << '\n';
        }
    }

    file_handler.close();
}