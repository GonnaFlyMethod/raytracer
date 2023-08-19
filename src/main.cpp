#include "common.h"
#include "datetime.h"
#include <chrono>
#include "color.h"
#include <fstream>
#include "hittable_list.h"
#include "camera.h"
#include "adding_objects_to_world.h"

// TODO:
// 1) Rename project in cmake lists(untitled1)

int main() {
    // World
    HittableList world = HittableList();
    add_objects_to_world(world);

    // Camera
    Camera cam;

    cam.aspect_ratio      = 16.0f / 9.0f;
    cam.image_width       = 1280;
    cam.samples_per_pixel = 50;
    cam.max_depth         = 50;

    cam.vfov     = 20;
    cam.lookfrom = Point3(13.0f, 2.0f, 3.0f);
    cam.lookat   = Point3(0.0f, 0.0f, 0.0f);
    cam.vup      = Vec3(0.0f, 1.0f, 0.0f);

    cam.defocus_angle = 0.6f;
    cam.focus_dist    = 10.0;

    std::map<size_t, std::vector<Color>> final_result;

    auto t1 = std::chrono::high_resolution_clock::now();
    // Render
    cam.render(world, final_result);
    auto t2 = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> ms_double = t2 - t1;

    std::clog << "Rendering took: "<< ms_double.count() / 1000 << "s " << std::endl;

    std::clog << "Constructing image..." << std::endl;

    std::string filename = "render_" + get_current_datetime() + ".ppm";

    std::ofstream file_handler;

    file_handler.open(filename, std::ios::out | std::ios::binary);

    file_handler << "P3\n" << cam.image_width << ' ' << cam.image_height << "\n255\n";

    for(auto& [ core_num, pixels_batch ] :  final_result){
        for (auto color : pixels_batch){
            write_color(file_handler, color, cam.samples_per_pixel);
        }
    }

    file_handler.close();

    return 0;
}
