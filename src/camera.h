#pragma once

#include <vector>
#include <map>

#include "common_math.h"
#include "vec3.h"
#include "ray.h"
#include "hittable_list.h"

struct BatchBoarder{
    int yStart;
    int yEnd;
};

struct CoreWork{
    int coreNum;
    std::vector<Color> workDone;
};

inline bool operator<(const CoreWork& lhs, const CoreWork& rhs);

class Camera {
private:
    Point3 camera_center;
    Point3 pixel_0_0_location;

    Vec3 pixel_delta_u; // Offset to pixel to the right
    Vec3 pixel_delta_v; // Offset to pixel below

    Vec3 u, v, w; // Camera frame bases vectors

    Vec3 defocus_disk_u;
    Vec3 defocus_disk_v;

    void initilize();

public:
    double aspect_ratio; // Ratio of image: width / height
    int image_width; // Rendered image width in pixel count
    int image_height; // Rendered image height
    int samples_per_pixel; // Count of random samples
    int max_depth; // Maximum number of Ray bounces

    double vfov; // Vertical field of view

    Point3 lookfrom; // Point camera is looking from
    Point3 lookat; // The target on which camera is looking at
    Vec3 vup;

    double defocus_angle; // Variation angle of rays through each pixel
    double focus_dist; // Distance from camera lookfrom position to the plane of perfect focus

    Color ray_color(const Ray& r, const HittableList &world, int depth);

    void render(const HittableList& world, std::map<size_t , std::vector<Color>>& final_work);

    [[nodiscard]] Ray get_ray(int i, int j) const;
    [[nodiscard]] Point3 defocus_disk_sample() const;
    [[nodiscard]] Vec3 pixel_sample_square() const;
};

