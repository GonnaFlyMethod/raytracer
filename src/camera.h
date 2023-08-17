#pragma once

#include <unordered_map>
#include <memory>
#include <future>
#include "common.h"
#include "material.h"
#include "color.h"


struct BatchBoarder{
    size_t xStart;
    size_t yStart;
    size_t xEnd;
    size_t yEnd;
};

struct CoreWork{
    size_t coreNum;
    std::vector<color> workDone;
};


class Camera{
private:
    int image_height; // Rendered image height
    point3 camera_center;
    point3 pixel_0_0_location;

    vec3 pixel_delta_u; // Offset to pixel to the right
    vec3 pixel_delta_v; // Offset to pixel below

    vec3 u, v, w; // Camera frame bases vectors

    vec3 defocus_disk_u;
    vec3 defocus_disk_v;

    void initilize(){
        image_height = static_cast<int>(image_width / aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height;

        camera_center = lookfrom;

        // Determine viewport dimensions.
        auto focal_length = (lookfrom - lookat).length();
        auto theta = degrees_to_radians(vfov);
        auto h = tan(theta/2);
        auto viewport_height = 2 * h * focus_dist;
        auto viewport_width = viewport_height * (static_cast<double>(image_width)/image_height);

        // Calculate the u,v,w unit basis vectors for the camera coordinate frame.
        w = unit_vector(lookfrom - lookat);
        u = unit_vector(cross(vup, w));
        v = cross(w, u);

        // Calculate the vectors across the horizontal and down the vertical viewport edges.
        vec3 viewport_u = viewport_width * u;    // Vector across viewport horizontal edge
        vec3 viewport_v = viewport_height * -v;  // Vector down viewport vertical edge

        // Calculate the horizontal and vertical delta vectors to the next pixel.
        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        // Calculate the location of the upper left pixel.
        auto viewport_upper_left = camera_center - (focus_dist * w) - viewport_u/2 - viewport_v/2;
        pixel_0_0_location = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

        // Calculate the camera defocus disk basis vectors.
        auto defocus_radius = focus_dist * tan(degrees_to_radians(defocus_angle / 2));
        defocus_disk_u = u * defocus_radius;
        defocus_disk_v = v * defocus_radius;
    }

public:
    double aspect_ratio = 1.0f; // Ratio of image: width / height
    int image_width = 100; // Rendered image width in pixel count
    int samples_per_pixel = 10; // Count of random samples
    int max_depth = 10; // Maximum number of ray bounces

    double vfov = 90; // Vertical field of view

    point3 lookfrom = point3(0.0f,0.0f,-1.0f); // Point camera is looking from
    point3 lookat = point3(0.0f,0.0f,0.0f); // The target on which camera is looking at
    vec3 vup = vec3(0.0f,1.0f,0.0f);

    double defocus_angle = 0; // Variation angle of rays through each pixel
    double focus_dist = 10; // Distance from camera lookfrom position to the plane of perfect focus

    color ray_color(const ray& r, const HittableList &world, int depth){
        hit_record rec;

        if (depth <= 0){
            return {0.0f,0.0f,0.0f};
        }

        if (world.hit(r,  0.001f, infinity, rec)){
            ray scattered;
            color attenuation;

            if (rec.mat_ptr->scatter(r, rec, attenuation, scattered)){
                return attenuation * ray_color(scattered, world, depth - 1);
            }

            return {0.0f,0.0f,0.0f};
        }

        vec3 unit_dir = unit_vector(r.GetDirection());
        double t = 0.5f * (unit_dir.y() + 1);

        color pixel_color = (1.0-t)*color(1.0, 1.0, 1.0);
        color pixel_color1 = t*color(0.5f, 0.7, 1.0);

        return pixel_color + pixel_color1;
    }

    void render(const HittableList& world) {
        this->initilize();

        std::size_t cores_available = std::thread::hardware_concurrency();

        const size_t pixels_in_row_for_each_thread = image_width / cores_available;
        const size_t left_over = image_width % cores_available;

        std::unordered_map<size_t, BatchBoarder> work_among_cores;
        size_t image_width_intervals = 0;

        for(int current_core = 1 ; current_core < cores_available + 1 ; current_core++){
            auto batch = BatchBoarder{};

            batch.xStart = image_width_intervals;
            image_width_intervals += pixels_in_row_for_each_thread;
            batch.xEnd = image_width_intervals;

            batch.yStart = 0;
            batch.yEnd = image_height;

            work_among_cores[current_core] = batch;
        }

        std::vector<std::future<CoreWork>> future_vector;

        for(const auto & [ core_num, batch ] :  work_among_cores){
            future_vector.emplace_back(
                    std::async([core_num, this, &world, &batch]{
                       CoreWork cw;
                       cw.coreNum = core_num;

                       for (size_t j = batch.yStart; j < batch.yEnd; ++j) {

//                            std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;

                           for (size_t i = batch.xStart; i < batch.xEnd; ++i) {

                               color pixel_color(0,0,0);

                               for (int sample = 0; sample < this->samples_per_pixel; ++sample) {
                                   // TODO: experiment with antialiasing for random [-1, 1)

                                   ray r = get_ray(i, j);
                                   pixel_color += ray_color(r, world, this->max_depth);
                               }

                               cw.workDone.push_back(pixel_color);
                           }
                       }

                       return cw;
                    }
            ));
        }

        int num_of_cores_finished = 0;

        while(num_of_cores_finished != cores_available){
            num_of_cores_finished = 0;

            for (auto &future: future_vector){
                if (future.valid()){
                    num_of_cores_finished++;
                }else{
                    std::clog << "Future is not valid" << std::endl;
                }
            }
        }


//        std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

        // construct image;

        std::clog << "\rDone.\n";
    }

    ray get_ray(int i, int j) const {
        // Get a randomly-sampled camera ray for the pixel at location i,j, originating from
        // the camera defocus disk.

        auto pixel_center = pixel_0_0_location + (i * pixel_delta_u) + (j * pixel_delta_v);
        auto pixel_sample = pixel_center + this->pixel_sample_square();

        auto ray_origin = (defocus_angle <= 0) ? camera_center : this->defocus_disk_sample();
        auto ray_direction = pixel_sample - ray_origin;

        return ray(ray_origin, ray_direction);
    }

    point3 defocus_disk_sample() const {
        // Returns a random point in the camera defocus disk.
        auto p = random_in_unit_disk();
        return camera_center + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
    }

    vec3 pixel_sample_square() const {
        // Returns a random point in the square surrounding a pixel at the origin.
        auto px = -0.5 + random_double();
        auto py = -0.5 + random_double();
        return (px * pixel_delta_u) + (py * pixel_delta_v);
    }
};
