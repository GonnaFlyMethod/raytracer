#include <ctime>
#include <sstream>
#include <iomanip>
#include <map>
#include <fstream>

#include "hittable_list.h"
#include "material.h"
#include "sphere.h"

void add_objects_to_world(HittableList& world){
    auto ground_material = make_shared<Lambertian>(
            Color(0.5f, 0.5f, 0.5f));
    world.add(make_shared<Sphere>(
            Point3(0.0f, -1000.0f, 0.0f), 1000, ground_material));

    for (int a = -11;a < 11;a++){
        for (int b = -11;b < 11;b++){
            double choose_mat = random_double();

            Point3 center(
                    a + 0.9f*random_double(),
                    0.2f,
                    b + 0.9*random_double());

            if ((center - Point3(4.0f, 0.2f, 0.0f)).length() > 0.9f){
                shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8f){
                    // Lambertian
                    Color albedo = Color::random() * Color::random();
                    sphere_material = make_shared<Lambertian>(albedo);
                    auto center2 = center + Vec3(0.0f, 0.5f, 0.0f);
                    world.add(
                            make_shared<Sphere>(center, center2, 0.2f, sphere_material)
                    );

                } else if (choose_mat < 0.95f){
                    // Metal
                    Color albedo = Color::random(0.5f, 1.0f);
                    double fuzz = random_double(0.0f, 0.5f);
                    sphere_material = make_shared<Metal>(albedo, fuzz);
                    world.add(
                            make_shared<Sphere>(center, 0.2f, sphere_material)
                    );
                } else{
                    // Glass
                    sphere_material = make_shared<Dielectric>(1.5);
                    world.add(
                            make_shared<Sphere>(center, 0.2f, sphere_material)
                    );
                }
            }
        }
    }

    auto material1 = make_shared<Dielectric>(1.5f);
    world.add(make_shared<Sphere>(
            Point3(0.0f, 1.0f, 0.0f), 1.0f, material1));

    auto material2 = make_shared<Lambertian>(Color(0.4f, 0.2f, 0.1f));
    world.add(make_shared<Sphere>(
            Point3(-4.0f, 1.0f, 0.0f), 1.0f, material2));

    auto material3 = make_shared<Metal>(Color(0.7f, 0.6f, 0.5f), 0.0f);
    world.add(make_shared<Sphere>(
            Point3(4.0f, 1.0f, 0.0f), 1.0f, material3));
}

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