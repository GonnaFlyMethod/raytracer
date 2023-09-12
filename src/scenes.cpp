#include "scenes.h"
#include "texture.h"
#include "material.h"
#include "sphere.h"

void random_spheres(HittableList& world, Camera& cam){
    auto checker_texture = make_shared<CheckerTexture>(
            0.32f, Color(0.2f, 0.3f, 0.1f), Color(0.9f, 0.9f, 0.9f));

    auto ground_material = make_shared<Lambertian>(checker_texture);
    world.add(make_shared<Sphere>(
            Point3(0.0f, -1000.0f, 0.0f), 1000.0f, ground_material));

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
                    sphere_material = make_shared<Dielectric>(1.5f);
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

    cam.aspect_ratio      = 16.0f / 9.0f;
    cam.image_width       = 320;
    cam.samples_per_pixel = 25;
    cam.max_depth         = 25;

    cam.vfov     = 20;
    cam.lookfrom = Point3(13.0f, 2.0f, 3.0f);
    cam.lookat   = Point3(0.0f, 0.0f, 0.0f);
    cam.vup      = Vec3(0.0f, 1.0f, 0.0f);

    cam.defocus_angle = 0.6f;
    cam.focus_dist    = 10.0;

}

void two_spheres_with_checker_texture(HittableList& world, Camera& cam){
    auto checker_texture = make_shared<CheckerTexture>(
            0.8f, Color(0.2f, 0.3f, 0.1f), Color(0.9f, 0.9f, 0.9f));

    auto ground_material = make_shared<Lambertian>(checker_texture);

    world.add(make_shared<Sphere>(
            Point3(0.0f, -10.0f, 0.0f), 10.0f, ground_material));

    world.add(make_shared<Sphere>(
            Point3(0.0f, 10.0f, 0.0f), 10.0f, ground_material));

    cam.aspect_ratio      = 16.0f / 9.0f;
    cam.image_width       = 640;
    cam.samples_per_pixel = 50;
    cam.max_depth         = 50;

    cam.vfov     = 20;
    cam.lookfrom = Point3(13.0f, 2.0f, 3.0f);
    cam.lookat   = Point3(0.0f, 0.0f, 0.0f);
    cam.vup      = Vec3(0.0f, 1.0f, 0.0f);
}

void earth(HittableList& world, Camera& cam){
    auto earth_texture = make_shared<ImageTexture>("earthmap.jpg");
    auto earth_surface = make_shared<Lambertian>(earth_texture);
    world.add(
            make_shared<Sphere>(Point3(0.0f, 0.0f, 0.0f), 2.0f, earth_surface));

    cam.aspect_ratio = 16.0f / 9.0f;
    cam.image_width = 400;
    cam.samples_per_pixel = 50;
    cam.max_depth = 50;

    cam.vfov = 20;
    cam.lookfrom = Point3(0.0f, 0.0f, 12.0f);
    cam.lookat = Point3(0.0f, 0.0f, 0.0f);
    cam.vup = Vec3(0.0f, 1.0f, 0.0f);

    cam.defocus_angle = 0;
}

void two_spheres_with_perlin_texture(HittableList& world, Camera& cam){
    auto perlin_texture = make_shared<PerlinTexture>(8.0f);
    auto lambertian_material = make_shared<Lambertian>(perlin_texture);

    world.add(make_shared<Sphere>(
            Point3(0.0f, -1000.0f, 0.0f), 1000.0f, lambertian_material));
    world.add(make_shared<Sphere>(
            Point3(0.0f, 2.0f, 0.0f), 2.0f, lambertian_material));

    cam.aspect_ratio = 16.0f / 9.0f;
    cam.image_width = 680;
    cam.samples_per_pixel = 50;
    cam.max_depth = 50;

    cam.vfov = 20;
    cam.lookfrom = Point3(13.0f, 2.0f, 3.0f);
    cam.lookat = Point3(0.0f, 0.0f, 0.0f);
    cam.vup = Vec3(0.0f ,1.0f, 0.0f);

    cam.defocus_angle = 0;
}