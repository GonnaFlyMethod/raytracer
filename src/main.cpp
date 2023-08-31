#include <chrono>

#include "file_writer.h"
#include "camera.h"
#include "bvh.h"
#include "scenes.h"

#define MAX_NUM_OF_SCENES 2;

// TODO:
// 1) Rename project in cmake lists(untitled1)

int main(int argc, char** argv) {
    int scene_to_draw = 1;

    if (argc > 1){
        // Converting char to integer by subtracting ASCII code of '0'
        int provided_scene_number = (*argv[1]) - '0';

        bool is_valid_scene_number = provided_scene_number > 0 && provided_scene_number <= MAX_NUM_OF_SCENES;

        if (!is_valid_scene_number){
            std::cout << "Incorrect number of scene. Default scene(1) will be drawn";
        }else{
            scene_to_draw = provided_scene_number;
        }

    }

    // Camera
    Camera cam;

    // World
    HittableList world = HittableList();

    switch (scene_to_draw) {
        case 2:
            std::clog << "2 Spheres will be drawn" << std::endl;

            two_spheres(world, cam);
            break;
        default:
            std::clog << "Random spheres will be drawn(default scene)" << std::endl;

            random_spheres(world, cam);
            break;
    }

    world = HittableList(make_shared<BoundingVolumeNode>(world));

    std::map<size_t, std::vector<Color>> final_result;

    auto t1 = std::chrono::high_resolution_clock::now();

    std::clog << "Rendering colors of pixels..." << std::endl;
    cam.render(world, final_result);

    std::clog << "Constructing image..." << std::endl;
    write_colors_into_file(
            final_result, cam.samples_per_pixel, cam.image_width, cam.get_calculated_image_height());

    auto t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> ms_double = t2 - t1;

    std::clog << "The whole process of rendering took: "<< ms_double.count() / 1000 << "s " << std::endl;

    return 0;
}
