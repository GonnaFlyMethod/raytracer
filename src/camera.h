#pragma once

#include <vector>
#include <map>

#include "./common_math/vec3.h"
#include "./common_math/ray.h"
#include "hittable_list.h"

struct BatchBoarder{
    int yStart;
    int yEnd;
};

struct CoreWork{
    int coreNum;
    std::vector<CommonMath::Color> workDone;
};

inline bool operator<(const CoreWork& lhs, const CoreWork& rhs);

class Camera {
private:
    CommonMath::Point3 camera_center;
    CommonMath::Point3 pixel_0_0_location;

    CommonMath::Vec3 pixel_delta_u; // Offset to pixel to the right
    CommonMath::Vec3 pixel_delta_v; // Offset to pixel below

    CommonMath::Vec3 u, v, w; // Camera frame bases vectors

    CommonMath::Vec3 defocus_disk_u;
    CommonMath::Vec3 defocus_disk_v;

    int image_height; // Rendered image height (calculated via constructor of camera)

    void initilize();

public:
    double aspect_ratio = 1.0; // Ratio of image: width / height
    int image_width = 100; // Rendered image width in pixel count
    int samples_per_pixel = 10; // Count of random samples
    int max_depth = 10; // Maximum number of Ray bounces

    double vfov = 90; // Vertical field of view

    CommonMath::Point3 lookfrom = CommonMath::Point3(0.0f, 0.0f, -1.0f); // Point camera is looking from
    CommonMath::Point3 lookat = CommonMath::Point3(0.0f, 1.0f, 0.0f); // The target on which camera is looking at
    CommonMath::Vec3 vup = CommonMath::Vec3(0.0f, 1.0f, 0.0f);

    double defocus_angle = 0.0f; // Variation angle of rays through each pixel
    double focus_dist = 10.0f; // Distance from camera lookfrom position to the plane of perfect focus

    int get_calculated_image_height() const;

    std::vector<double> convert_to_clip_space_coords(CommonMath::Vec3 input_vector) const;

    CommonMath::Color ray_color(const CommonMath::Ray& r, const HittableList &world, int depth);

    void render(const HittableList& world, std::map<size_t , std::vector<CommonMath::Color>>& final_work);

    [[nodiscard]] CommonMath::Ray get_ray(int i, int j) const;
    [[nodiscard]] CommonMath::Point3 defocus_disk_sample() const;
    [[nodiscard]] CommonMath::Vec3 pixel_sample_square() const;
};
