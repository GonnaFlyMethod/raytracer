#include "adding_objects_to_world.h"
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
                    world.add(
                            make_shared<Sphere>(center, 0.2f, sphere_material)
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