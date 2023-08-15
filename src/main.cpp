#include "common.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"

int main() {
    // World
    HittableList world = HittableList();

    auto ground_material = make_shared<Lambertian>(
            color(0.5f, 0.5f, 0.5f));
    world.add(make_shared<Sphere>(
            point3(0.0f, -1000.0f, 0.0f), 1000, ground_material));

    for (int a = -11;a < 11;a++){
        for (int b = -11;b < 11;b++){
            double choose_mat = random_double();

            point3 center(
                    a + 0.9f*random_double(),
                    0.2f,
                    b + 0.9*random_double());

            if ((center - point3(4.0f, 0.2f, 0.0f)).length() > 0.9f){
                shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8f){
                    // Lambertian
                    color albedo = color::random() * color::random();
                    sphere_material = make_shared<Lambertian>(albedo);
                    world.add(
                            make_shared<Sphere>(center, 0.2f, sphere_material)
                            );

                } else if (choose_mat < 0.95f){
                    // Metal
                    color albedo = color::random(0.5f, 1.0f);
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
            point3(0.0f, 1.0f, 0.0f), 1.0f, material1));

    auto material2 = make_shared<Lambertian>(color(0.4f, 0.2f, 0.1f));
    world.add(make_shared<Sphere>(
            point3(-4.0f, 1.0f, 0.0f), 1.0f, material2));

    auto material3 = make_shared<Metal>(color(0.7f, 0.6f, 0.5f), 0.0f);
    world.add(make_shared<Sphere>(
            point3(4.0f, 1.0f, 0.0f), 1.0f, material3));

    // Camera
    Camera cam;

    cam.aspect_ratio      = 16.0f / 9.0f;
    cam.image_width       = 640;
    cam.samples_per_pixel = 20;
    cam.max_depth         = 25;

    cam.vfov     = 20;
    cam.lookfrom = point3(13.0f,2.0f,3.0f);
    cam.lookat   = point3(0.0f,0.0f,0.0f);
    cam.vup      = vec3(0.0f,1.0f,0.0f);

    cam.defocus_angle = 0.6f;
    cam.focus_dist    = 10.0;

    // Render
    cam.render(world);

    return 0;
}
