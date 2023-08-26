#include "main_helpers.h"
#include <chrono>
#include "camera.h"
#include "bvh.h"

// TODO:
// 1) Rename project in cmake lists(untitled1)

int main() {
    // World
    HittableList world = HittableList();
    add_objects_to_world(world);

    world = HittableList(make_shared<BoundingVolumeNode>(world));

    // Camera
    Camera cam;

    cam.aspect_ratio      = 16.0f / 9.0f;
    cam.image_width       = 400;
    cam.samples_per_pixel = 10;
    cam.max_depth         = 10;

    cam.vfov     = 20;
    cam.lookfrom = Point3(13.0f, 2.0f, 3.0f);
    cam.lookat   = Point3(0.0f, 0.0f, 0.0f);
    cam.vup      = Vec3(0.0f, 1.0f, 0.0f);

    cam.defocus_angle = 0.6f;
    cam.focus_dist    = 10.0;

    std::map<size_t, std::vector<Color>> final_result;

    auto t1 = std::chrono::high_resolution_clock::now();

    std::clog << "Rendering colors of pixels..." << std::endl;
    cam.render(world, final_result);

    std::clog << "Constructing image..." << std::endl;
    write_colors_into_file(final_result, cam.samples_per_pixel, cam.image_width, cam.image_height);

    auto t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> ms_double = t2 - t1;

    std::clog << "The whole process of rendering took: "<< ms_double.count() / 1000 << "s " << std::endl;

    return 0;
}
