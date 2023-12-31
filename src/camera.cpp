#include <future>

#include "camera.h"

#include "material.h"
#include "common_math/triginometry.h"

void Camera::initilize(){
    image_height = static_cast<int>(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // TODO: get rid of this alias
    camera_center = lookfrom;

    // Determine viewport dimensions.
    auto theta = CommonMath::degrees_to_radians(vfov);
    auto h = tan(theta/2);

    // TODO: move these 2 members to local scope of this function
    viewport_height = 2 * h * focus_dist;
    viewport_width = viewport_height * (static_cast<double>(image_width)/image_height);

    // Calculate the u,v,w unit basis vectors for the camera coordinate frame.
    w = unit_vector(lookfrom - lookat);
    u = unit_vector(cross(vup, w));
    v = cross(w, u);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    CommonMath::Vec3 viewport_u = viewport_width * u;    // Vector across viewport horizontal edge
    CommonMath::Vec3 viewport_v = viewport_height * -v;  // Vector down viewport vertical edge

    // Calculate the horizontal and vertical delta vectors to the next pixel.
    pixel_delta_u = viewport_u / image_width;
    pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel.
    auto viewport_upper_left = camera_center - (focus_dist * w) - viewport_u/2 - viewport_v/2;
    pixel_0_0_location = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // Calculate the camera defocus disk basis vectors.
    auto defocus_radius = focus_dist * tan(CommonMath::degrees_to_radians(defocus_angle / 2));
    defocus_disk_u = u * defocus_radius;
    defocus_disk_v = v * defocus_radius;
}

int Camera::get_calculated_image_height() const{
    return image_height;
}

std::vector<double> Camera::convert_to_clip_space_coords(CommonMath::Vec3 input_vector) const {
    double vec_to_work_with[4] = {input_vector.x(), input_vector.y(), input_vector.z(), 1};

    // Set near plane and far plane according to the actual distance from camera of nearest object and
    // farthest object in the scene

    double near_plane = 0.001f;
    double far_plane = 9000 * 2 * tan(this->vfov / 2);

//    double projection_matrix[4][4] = {{1.0, 0.0, 0.0,                                                      0.0},
//                                      {0.0, 1.0, 0.0,                                                      0.0},
//                                      {0.0, 0.0, -1.0,                                                     -1.0},
//                                      {0.0, 0.0,
//                                          -2.0 * near_plane * far_plane / (far_plane - near_plane),
//                                          near_plane + far_plane / (far_plane - near_plane)}};

    double projection_matrix[4][4] = {{1.0, 0.0, 0.0, 0.0},
                                      {0.0, 1.0, 0.0, 0.0},
                                      {0.0, 0.0, 1.0, 0.0f},
                                      {0.0, 0.0, 0.0f, 1.0f}};

    std::vector<double> result{0.0f,0.0f,0.0f,0.0f};

    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            double matrix_element = projection_matrix[i][j];
            result[i] += matrix_element * vec_to_work_with[j];
        }
    }

    return result;
}

CommonMath::Color Camera::ray_color(const CommonMath::Ray &r, const HittableList &world, int depth) {
    hit_record rec;

    if (depth <= 0){
        return {0.0f,0.0f,0.0f};
    }

    Interval hit_interval(0.001f, CommonMath::infinity);

    if (world.hit(r, hit_interval, rec)){
        CommonMath::Ray scattered;
        CommonMath::Color attenuation;

        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered)){
            CommonMath::Color r = ray_color(scattered, world, depth - 1);
            return attenuation * ray_color(scattered, world, depth - 1);
        }

        return {0.0f,0.0f,0.0f};
    }

    CommonMath::Vec3 unit_dir = unit_vector(r.GetDirection());
    double t = 0.5f * (unit_dir.y() + 1);

    CommonMath::Color pixel_color = (1.0 - t) * CommonMath::Color(1.0, 1.0, 1.0);
    CommonMath::Color pixel_color1 = t * CommonMath::Color(0.5f, 0.7, 1.0);

    return pixel_color + pixel_color1;
}

void Camera::render(const HittableList &world, std::map<size_t, std::vector<CommonMath::Color>> &final_work) {
    this->initilize();

    int cores_available = static_cast<int>(std::thread::hardware_concurrency());

    const int pixels_in_row_for_each_thread = image_height / cores_available;

    std::map<int, BatchBoarder> work_among_cores;
    int image_height_intervals = 0;

    for(int current_core = 1 ; current_core < cores_available + 1 ; current_core++){
        auto batch_boarder = BatchBoarder{};

        batch_boarder.yStart = image_height_intervals;
        image_height_intervals += pixels_in_row_for_each_thread;
        batch_boarder.yEnd = image_height_intervals;

        work_among_cores[current_core] = batch_boarder;
    }

    const int left_over = image_height % cores_available;
    work_among_cores[cores_available].yEnd += left_over;

    std::vector<std::future<CoreWork>> future_vector;
    future_vector.reserve(work_among_cores.size());

    for(const auto & [ core_num, batch ] :  work_among_cores){
        future_vector.emplace_back(
            std::async([batch, core_num, this, &world]{
                CoreWork cw;
                cw.coreNum = core_num;

                for (int j = batch.yStart; j < batch.yEnd; ++j) {
                    double raw_percentage = static_cast<double>(j) / static_cast<double>(this->image_height);

                    std::string core_work_progress = "[CPU Core " + std::to_string(core_num) + "]" +
                        " Rows calculated: " + std::to_string(raw_percentage * 100) + " %\n";

                    std::clog << core_work_progress;

                    for (int i = 0; i < this->image_width; ++i) {
                        CommonMath::Color pixel_color(0, 0, 0);

                        for (int sample = 0; sample < this->samples_per_pixel; ++sample) {
                            // TODO: experiment with antialiasing for random [-1, 1)

                            CommonMath::Ray r = get_ray(i, j);
                            pixel_color += ray_color(r, world, this->max_depth);
                        }

                        cw.workDone.push_back(pixel_color);

                    }
                }

                return cw;
            }));
    }

    for (auto  &future: future_vector){
        CoreWork cw = future.get();
        final_work[cw.coreNum] = cw.workDone;
    }
}

CommonMath::Ray Camera::get_ray(int i, int j) const {
    // Get a randomly-sampled camera Ray for the pixel at location i,j, originating from
    // the camera defocus disk

    auto pixel_center = pixel_0_0_location + (i * pixel_delta_u) + (j * pixel_delta_v);
    auto pixel_sample = pixel_center + this->pixel_sample_square();

    auto ray_origin = (defocus_angle <= 0) ? camera_center : this->defocus_disk_sample();
    auto ray_direction = pixel_sample - ray_origin;

    double random_time = CommonMath::random_double();

    return {ray_origin, ray_direction, random_time};
}

CommonMath::Point3 Camera::defocus_disk_sample() const {
    // Returns a random point in the camera defocus disk

    auto p = CommonMath::random_in_unit_disk();
    return camera_center + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
}

CommonMath::Vec3 Camera::pixel_sample_square() const {
    // Returns a random point in the square surrounding a pixel at the origin

    auto px = -0.5 + CommonMath::random_double();
    auto py = -0.5 + CommonMath::random_double();
    return (px * pixel_delta_u) + (py * pixel_delta_v);
}