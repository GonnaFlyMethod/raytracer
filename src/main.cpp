#include <chrono>
#include <memory>

#include "file_writer.h"
#include "camera.h"
#include "scenes.h"
#include "bvh.h"

#define MAX_NUM_OF_SCENES 4;

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
            std::clog << "2 Spheres with checker texture will be drawn" << '\n';

            two_spheres_with_checker_texture(world, cam);
            break;
        case 3:
            std::clog << "Lambertian sphere with Earth texture will be drawn" << '\n';

            earth(world, cam);
            break;
        case 4:
            std::clog << "2 Spheres with perlin texture will be drawn" << '\n';

            two_spheres_with_perlin_texture(world, cam);
            break;
        default:
            std::clog << "Random spheres will be drawn(default scene)" << '\n';

            random_spheres(world, cam);
            break;
    }

    world = HittableList(std::make_shared<BoundingVolumeNode>(world));

    std::map<size_t, std::vector<CommonMath::Color>> final_result;

    std::clog << "Rendering colors of pixels..." << '\n';

    auto t1 = std::chrono::high_resolution_clock::now();
    cam.render(world, final_result);

    std::clog << "Constructing image..." << '\n';
    write_colors_into_file(
            final_result, cam.samples_per_pixel, cam.image_width, cam.get_calculated_image_height());

    auto t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> ms_double = t2 - t1;

    std::clog << "The whole process of rendering took: "<< ms_double.count() / 1000 << "s " << '\n';

    return 0;
}
