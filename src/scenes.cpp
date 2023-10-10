#include "scenes.h"
#include "material.h"
#include "primitives/sphere.h"
#include "primitives/quad.h"
#include "primitives/triangle.h"

void random_spheres(HittableList& world, Camera& cam){
    auto checker_texture = std::make_shared<CheckerTexture>(
            0.32f, CommonMath::Color(0.2f, 0.3f, 0.1f), CommonMath::Color(0.9f, 0.9f, 0.9f));

    auto ground_material = std::make_shared<Lambertian>(checker_texture);
    world.add(std::make_shared<Sphere>(
            CommonMath::Point3(0.0f, -1000.0f, 0.0f), 1000.0f, ground_material));

    for (int a = -11;a < 11;a++){
        for (int b = -11;b < 11;b++){
            double choose_mat = CommonMath::random_double();

            CommonMath::Point3 center(
                    a + 0.9f*CommonMath::random_double(),
                    0.2f,
                    b + 0.9*CommonMath::random_double());

            if ((center - CommonMath::Point3(4.0f, 0.2f, 0.0f)).length() > 0.9f){
                std::shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8f){
                    // Lambertian
                    CommonMath::Color albedo = CommonMath::Color::random() * CommonMath::Color::random();
                    sphere_material = std::make_shared<Lambertian>(albedo);
                    auto center2 = center + CommonMath::Vec3(0.0f, 0.5f, 0.0f);
                    world.add(
                            std::make_shared<Sphere>(center, center2, 0.2f, sphere_material)
                    );

                } else if (choose_mat < 0.95f){
                    // Metal
                    CommonMath::Color albedo = CommonMath::Color::random(0.5f, 1.0f);
                    double fuzz = CommonMath::random_double(0.0f, 0.5f);
                    sphere_material = std::make_shared<Metal>(albedo, fuzz);
                    world.add(
                            std::make_shared<Sphere>(center, 0.2f, sphere_material)
                    );
                } else{
                    // Glass
                    sphere_material = std::make_shared<Dielectric>(1.5f);
                    world.add(
                            std::make_shared<Sphere>(center, 0.2f, sphere_material)
                    );
                }
            }
        }
    }

    auto material1 = std::make_shared<Dielectric>(1.5f);
    world.add(std::make_shared<Sphere>(
            CommonMath::Point3(0.0f, 1.0f, 0.0f), 1.0f, material1));

    auto material2 = std::make_shared<Lambertian>(CommonMath::Color(0.4f, 0.2f, 0.1f));
    world.add(std::make_shared<Sphere>(
            CommonMath::Point3(-4.0f, 1.0f, 0.0f), 1.0f, material2));

    auto material3 = std::make_shared<Metal>(CommonMath::Color(0.7f, 0.6f, 0.5f), 0.0f);
    world.add(std::make_shared<Sphere>(
            CommonMath::Point3(4.0f, 1.0f, 0.0f), 1.0f, material3));

    cam.aspect_ratio      = 16.0f / 9.0f;
    cam.image_width       = 320;
    cam.samples_per_pixel = 25;
    cam.max_depth         = 25;

    cam.vfov     = 20;
    cam.lookfrom = CommonMath::Point3(13.0f, 2.0f, 3.0f);
    cam.lookat   = CommonMath::Point3(0.0f, 0.0f, 0.0f);
    cam.vup      = CommonMath::Vec3(0.0f, 1.0f, 0.0f);

    cam.defocus_angle = 0.6f;
    cam.focus_dist    = 10.0;

}

void two_spheres_with_checker_texture(HittableList& world, Camera& cam){
    auto checker_texture = std::make_shared<CheckerTexture>(
            0.8f, CommonMath::Color(0.2f, 0.3f, 0.1f), CommonMath::Color(0.9f, 0.9f, 0.9f));

    auto ground_material = std::make_shared<Lambertian>(checker_texture);

    world.add(std::make_shared<Sphere>(
            CommonMath::Point3(0.0f, -10.0f, 0.0f), 10.0f, ground_material));

    world.add(std::make_shared<Sphere>(
            CommonMath::Point3(0.0f, 10.0f, 0.0f), 10.0f, ground_material));

    cam.aspect_ratio      = 16.0f / 9.0f;
    cam.image_width       = 640;
    cam.samples_per_pixel = 50;
    cam.max_depth         = 50;

    cam.vfov     = 20;
    cam.lookfrom = CommonMath::Point3(13.0f, 2.0f, 3.0f);
    cam.lookat   = CommonMath::Point3(0.0f, 0.0f, 0.0f);
    cam.vup      = CommonMath::Vec3(0.0f, 1.0f, 0.0f);
}

void earth(HittableList& world, Camera& cam){
    auto earth_texture = std::make_shared<ImageTexture>("earthmap.jpg");
    auto earth_surface = std::make_shared<Lambertian>(earth_texture);
    world.add(
            std::make_shared<Sphere>(CommonMath::Point3(0.0f, 0.0f, 0.0f), 2.0f, earth_surface));

    cam.aspect_ratio = 16.0f / 9.0f;
    cam.image_width = 400;
    cam.samples_per_pixel = 50;
    cam.max_depth = 50;

    cam.vfov = 20;
    cam.lookfrom = CommonMath::Point3(0.0f, 0.0f, 12.0f);
    cam.lookat = CommonMath::Point3(0.0f, 0.0f, 0.0f);
    cam.vup = CommonMath::Vec3(0.0f, 1.0f, 0.0f);

    cam.defocus_angle = 0;
}

void two_spheres_with_perlin_texture(HittableList& world, Camera& cam){
    auto perlin_texture = std::make_shared<PerlinTexture>(4.0f);
    auto lambertian_material = std::make_shared<Lambertian>(perlin_texture);

    world.add(std::make_shared<Sphere>(
            CommonMath::Point3(0.0f, -1000.0f, 0.0f), 1000.0f, lambertian_material));
    world.add(std::make_shared<Sphere>(
            CommonMath::Point3(0.0f, 2.0f, 0.0f), 2.0f, lambertian_material));

    cam.aspect_ratio = 16.0f / 9.0f;
    cam.image_width = 480;
    cam.samples_per_pixel = 50;
    cam.max_depth = 50;

    cam.vfov = 20;
    cam.lookfrom = CommonMath::Point3(13.0f, 2.0f, 3.0f);
    cam.lookat = CommonMath::Point3(0.0f, 0.0f, 0.0f);
    cam.vup = CommonMath::Vec3(0.0f ,1.0f, 0.0f);

    cam.defocus_angle = 0;
}

void quads(HittableList& world, Camera& cam){
    auto left_red     = std::make_shared<Lambertian>(
            CommonMath::Color(1.0f, 0.2f, 0.2f));
    auto back_green   = std::make_shared<Lambertian>(
            CommonMath::Color(0.2f, 1.0f, 0.2f));
    auto right_blue   = std::make_shared<Lambertian>(
            CommonMath::Color(0.2f, 0.2f, 1.0f));
    auto upper_orange = std::make_shared<Lambertian>(
            CommonMath::Color(1.0f, 0.5f, 0.0f));
    auto lower_teal   = std::make_shared<Lambertian>(
            CommonMath::Color(0.2f, 0.8f, 0.8f));

    world.add(std::make_shared<Quad>(
            CommonMath::Point3(-3.0f,-2.0f, 5.0f),
            CommonMath::Vec3(0.0f, 0.0f,-4.0f),
            CommonMath::Vec3(0.0f, 4.0f, 0.0f),
            left_red));

    world.add(
            std::make_shared<Quad>(
                    CommonMath::Point3(-2.0f,-2.0f, 0.0f),
                    CommonMath::Vec3(4.0f, 0.0f, 0.0f),
                    CommonMath::Vec3(0.0f, 4.0f, 0.0f),
                    back_green));

    world.add(
            std::make_shared<Quad>(
                    CommonMath::Point3( 3.0f,-2.0f, 1.0f),
                    CommonMath::Vec3(0.0f, 0.0f, 4.0f),
                    CommonMath::Vec3(0.0f, 4.0f, 0.0f),
                    right_blue));
    world.add(
            std::make_shared<Quad>(
                    CommonMath::Point3(-2.0f, 3.0f, 1.0f),
                    CommonMath::Vec3(4.0f, 0.0f, 0.0f),
                    CommonMath::Vec3(0.0f, 0.0f, 4.0f),
                    upper_orange));
    world.add(
            std::make_shared<Quad>(
                    CommonMath::Point3(-2.0f,-3.0f, 5.0f),
                    CommonMath::Vec3(4.0f, 0.0f, 0.0f),
                    CommonMath::Vec3(0.0f, 0.0f,-4.0f),
                    lower_teal));

    cam.aspect_ratio = 16.0f / 9.0f;
    cam.image_width = 400;
    cam.samples_per_pixel = 50;
    cam.max_depth = 50;

    cam.vfov = 80;
    cam.lookfrom = CommonMath::Point3(0.0f,0.0f,9.0f);
    cam.lookat   = CommonMath::Point3(0.0f,0.0f,0.0f);
    cam.vup      = CommonMath::Vec3(0.0f,1.0f,0.0f);

    cam.defocus_angle = 0;
}

void triangles(HittableList& world, Camera& cam){
    cam.aspect_ratio = 16.0f / 9.0f;
    cam.image_width = 400;
    cam.samples_per_pixel = 50;
    cam.max_depth = 50;

    cam.vfov = 80.0f;
    cam.lookfrom = CommonMath::Point3(0.0f,0.0f,4.0f);
    cam.lookat   = CommonMath::Point3(0.0f,0.0f,0.0f);
    cam.vup      = CommonMath::Vec3(0.0f,1.0f,0.0f);

    cam.defocus_angle = 0;

    auto earth_texture = std::make_shared<ImageTexture>("earthmap_resized.jpg");
    auto lambertian_with_earth_texture= std::make_shared<Lambertian>(earth_texture);

    auto bricks_texture = std::make_shared<ImageTexture>("bricks.jpg");
    auto lambertian_with_bricks_texture = std::make_shared<Lambertian>(bricks_texture);

//    world.add(std::make_shared<Triangle>(
//            CommonMath::Point3(-1.5f,-1.0f, 0.0f),
//            CommonMath::Point3(-0.2f,3.0f, 0.0f),
//            CommonMath::Point3(-0.0f,-1.0f, -2.0f),
//            lambertian_with_bricks_texture, cam));

    world.add(std::make_shared<Triangle>(
            CommonMath::Point3(-5.5f,2.0f, 0.0f),
            CommonMath::Point3(-3.5f,-2.5f, -1.0f),
            CommonMath::Point3(-2.5f,1.0f, -2.0f),
            lambertian_with_earth_texture, cam));

//    world.add(std::make_shared<Triangle>(
//            CommonMath::Point3(0.5f,0.0f, 0.0f),
//            CommonMath::Point3(2.5f,2.0f, 0.0f),
//            CommonMath::Point3(5.5f,0.0f, 0.0f),
//            lambertian_with_bricks_texture, cam));

//    world.add(std::make_shared<Triangle>(
//            CommonMath::Point3(0.0f,-3.0f, -5.0f),
//            CommonMath::Point3(2.0f,-1.0f, 0.0f),
//            CommonMath::Point3(5.0f,-3.0f, 0.0f),
//            lambertian_with_earth_texture, cam));
}
