#include <algorithm>
#include "triangle.h"
#include "../external/glm/glm.hpp"
#include "../external/glm/ext/matrix_transform.hpp"
#include "../external/glm/ext/matrix_clip_space.hpp"
#include "../common_math/other.h"
#include "../common_math/mat4.h"
#include "../common_math/mat4_transform.h"
#include "../common_math/vec4.h"


Triangle::Triangle(
        CommonMath::Point3 vertex0,
        CommonMath::Point3 vertex1,
        CommonMath::Point3 vertex2,
        std::shared_ptr<Material> _mat_ptr, Camera& camera)
    : PlaceableOnPlane(vertex0, vertex1 - vertex0, vertex2 - vertex0), mat_ptr(_mat_ptr) {

    // TODO: move to the other type of initialization
    this->vertex0 = vertex0;
    this->vertex1 = vertex1;
    this->vertex2 = vertex2;

    this->vertex0_vertex1_edge = vertex1 - vertex0;
    this->vertex1_vertex2_edge = vertex2 - vertex1;
    this->vertex2_vertex0_edge = vertex0 - vertex2;

    this->cam = camera;

    CommonMath::Vec3 center_of_original_triangle = CommonMath::Vec3(
            (vertex0.x() + vertex1.x() + vertex2.x()) / 3.0f,
            (vertex0.y() + vertex1.y() + vertex2.y()) / 3.0f,
            (vertex0.z() + vertex1.z() + vertex2.z()) / 3.0f);

    CommonMath::Vec3 center_to_vertex0_vec =  (vertex0 - center_of_original_triangle);
    double center_to_vertex0_vec_length = center_to_vertex0_vec.length();
    CommonMath::Vec3 normalized_center_to_vertex0_vec = center_to_vertex0_vec.normalize();
    this->vertex0_in_local_space = normalized_center_to_vertex0_vec * center_to_vertex0_vec_length;

    CommonMath::Vec3 center_to_vertex1_vec =  (vertex1 - center_of_original_triangle);
    double center_to_vertex1_vec_length = center_to_vertex1_vec.length();
    CommonMath::Vec3 normalized_center_to_vertex1_vec = center_to_vertex1_vec.normalize();
    this->vertex1_in_local_space = normalized_center_to_vertex1_vec * center_to_vertex1_vec_length;

    CommonMath::Vec3 center_to_vertex2_vec =  (vertex2 - center_of_original_triangle);
    double center_to_vertex2_vec_length = center_to_vertex2_vec.length();
    CommonMath::Vec3 normalized_center_to_vertex2_vec = center_to_vertex2_vec.normalize();
    this->vertex2_in_local_space = normalized_center_to_vertex2_vec * center_to_vertex2_vec_length;

    std::vector<CommonMath::Point3> vertices_in_local_space{
        vertex0_in_local_space,
        vertex1_in_local_space,
        vertex2_in_local_space};

    std::sort(vertices_in_local_space.begin(), vertices_in_local_space.end(),
              [&](const CommonMath::Vec3& a, const CommonMath::Vec3& b) -> bool{
                  return a.x() < b.x();
              });

    left_x_for_projection = vertices_in_local_space[0].x();
    right_x_for_projection = vertices_in_local_space[2].x(),

    std::sort(vertices_in_local_space.begin(), vertices_in_local_space.end(),
              [&](const CommonMath::Vec3& a, const CommonMath::Vec3& b) -> bool{
                  return a.y() < b.y();
              });

    bottom_y_for_projection = vertices_in_local_space[0].y(),
    top_y_for_projection = vertices_in_local_space[2].y();

    double original_width{};

    if (left_x_for_projection < 0 && right_x_for_projection > 0){
        original_width = std::abs(left_x_for_projection) + std::abs(right_x_for_projection);
    }else{
        original_width = std::abs(std::abs(right_x_for_projection) - std::abs(left_x_for_projection));
    }

    double original_height{};

    if (bottom_y_for_projection < 0 && top_y_for_projection > 0){
        original_height = std::abs(bottom_y_for_projection) + std::abs(top_y_for_projection);
    }else{
        original_height = std::abs(std::abs(top_y_for_projection) - std::abs(bottom_y_for_projection));
    }

    double original_height_multiplied_by_2 = original_height * 2.0f;

    if (original_width < original_height_multiplied_by_2){
        double delta_width = original_height_multiplied_by_2 - original_width;
        double half_of_padding = delta_width / 2.0f;

        left_x_for_projection -= half_of_padding;
        right_x_for_projection += half_of_padding;
    }else if (original_width > original_height_multiplied_by_2){
        double delta_height = original_width - original_height_multiplied_by_2;
        double half_of_padding = delta_height / 2.0f;

        bottom_y_for_projection -= half_of_padding;
        top_y_for_projection += half_of_padding;
    }

    std::sort(vertices_in_local_space.begin(), vertices_in_local_space.end(),
              [&](const CommonMath::Vec3& a, const CommonMath::Vec3& b) -> bool{
                  return a.z() < b.z();
              });

    double farthest_object_z = vertices_in_local_space[2].z();
    double camera_lookfrom_z = cam.lookfrom.z();

    if (farthest_object_z < 0 && camera_lookfrom_z > 0 || farthest_object_z > 0 && camera_lookfrom_z < 0){
        farthest_z_for_projection = std::abs(farthest_object_z) + std::abs(camera_lookfrom_z);
    }else{
        farthest_z_for_projection = std::abs(std::abs(farthest_object_z) - std::abs(camera_lookfrom_z));
    }
}

AABB Triangle::get_bounding_box() const {
    return this->box;
}


bool Triangle::hit(const CommonMath::Ray &r, Interval ray_t, hit_record &rec) const {
    double appropriate_direction_scaler;

    if (!this->does_hit_plane(r, ray_t, appropriate_direction_scaler)){
        return false;
    }

    CommonMath::Point3 intersection_point = r.at(appropriate_direction_scaler);

    double a = this->vertex0_vertex1_edge.length();
    double b = this->vertex1_vertex2_edge.length();
    double c = this->vertex2_vertex0_edge.length();

    double area_of_whole_triangle = CommonMath::calculate_area_of_triangle(a , b, c );

    double v0_intersection_point_vec = (intersection_point - vertex0).length();
    double v1_intersection_point_vec = (intersection_point - vertex1).length();
    double v2_intersection_point_vec = (intersection_point - vertex2).length();

    double alpha = CommonMath::calculate_area_of_triangle(
            v1_intersection_point_vec,
            v2_intersection_point_vec,
            b) / area_of_whole_triangle;

    if (alpha < 0){
        return false;
    }

    double beta = CommonMath::calculate_area_of_triangle(
            v0_intersection_point_vec,
            v2_intersection_point_vec,
            c) / area_of_whole_triangle;

    if (beta < 0){
        return false;
    }

    double gamma = CommonMath::calculate_area_of_triangle(
            v0_intersection_point_vec,
            v1_intersection_point_vec,
            a) / area_of_whole_triangle;

    if (gamma < 0){
        return false;
    }

    if (alpha + beta + gamma > 1.0001f){
        return false;
    }

    // TODO: finilize and explain the stretching of square texture during the process of blending between
    //  uv coordinates of triangle's vertices using barycentric weights

    // TODO: try resized earthmap texture

    glm::vec3 position(cam.lookfrom.x(), cam.lookfrom.y(), cam.lookfrom.z()); // Camera position

    glm::vec3 target(0.0f,
            0.0f,
            0.0f);

    glm::vec3 up(cam.vup.x(), cam.vup.y(), cam.vup.z());      // Up vector

    // Custom section
    // TODO: The final vector (vertex_0_in_clip_space_custom) contains incorrect values:
    CommonMath::Mat4 view_matrix = CommonMath::look_at_for_view_projection(
            CommonMath::Vec3(position.x, position.y, position.z),
            CommonMath::Vec3(0.0, 0.0, 0.0),
            CommonMath::Vec3(cam.vup.x(), cam.vup.y(), cam.vup.z()));

    CommonMath::Mat4 orthographic_projection = CommonMath::orthographic_projection(
            this->left_x_for_projection,
            this->right_x_for_projection,
            this->bottom_y_for_projection,
            this->top_y_for_projection,
            0.1,
            this->farthest_z_for_projection
    );

    CommonMath::Vec4 vertex_0_in_clip_space_custom = orthographic_projection * view_matrix * CommonMath::Vec4(
            vertex0_in_local_space.x(),
            vertex0_in_local_space.y(),
            vertex0_in_local_space.z(), 1.0f);

    CommonMath::Vec4 vertex_1_in_clip_space_custom = orthographic_projection * view_matrix * CommonMath::Vec4(
            vertex1_in_local_space.x(),
            vertex1_in_local_space.y(),
            vertex1_in_local_space.z(), 1.0f);

    CommonMath::Vec4 vertex_2_in_clip_space_custom = orthographic_projection * view_matrix * CommonMath::Vec4(
            vertex2_in_local_space.x(),
            vertex2_in_local_space.y(),
            vertex2_in_local_space.z(), 1.0f);

    // Custom section
    glm::mat4 viewMatrix = glm::lookAt(position, target, up);

    glm::mat4 projectionMatrix = glm::ortho(
            left_x_for_projection,
            right_x_for_projection,
            bottom_y_for_projection,
            top_y_for_projection, 0.1, farthest_z_for_projection);

    glm::vec4 vertex_0_in_clip_space = projectionMatrix * viewMatrix * glm::vec4(
            vertex0_in_local_space.x(),
            vertex0_in_local_space.y(),
            vertex0_in_local_space.z(), 1.0f);

    glm::vec4 vertex_1_in_clip_space = projectionMatrix * viewMatrix * glm::vec4(
            vertex1_in_local_space.x(),
            vertex1_in_local_space.y(),
            vertex1_in_local_space.z(), 1.0f);

    glm::vec4 vertex_2_in_clip_space = projectionMatrix * viewMatrix * glm::vec4(
            vertex2_in_local_space.x(),
            vertex2_in_local_space.y(),
            vertex2_in_local_space.z(), 1.0f);

    glm::vec3 vertex_0_in_normalized_device_space = glm::vec3(
            CommonMath::clamp(vertex_0_in_clip_space.x * 0.5 + 0.5, 0.0, 1.0),
            CommonMath::clamp(vertex_0_in_clip_space.y  * 0.5 + 0.5, 0.0, 1.0),
            vertex_0_in_clip_space.z  * 0.5 + 0.5);

    glm::vec3 vertex_1_in_normalized_device_space = glm::vec3(
            CommonMath::clamp(vertex_1_in_clip_space.x  * 0.5 + 0.5, 0.0, 1.0),
            CommonMath::clamp(vertex_1_in_clip_space.y  * 0.5 + 0.5, 0, 1.0),
            vertex_1_in_clip_space.z  * 0.5 + 0.5);

    glm::vec3 vertex_2_in_normalized_device_space = glm::vec3(
            CommonMath::clamp(vertex_2_in_clip_space.x  * 0.5 + 0.5, 0.0, 1.0),
            CommonMath::clamp(vertex_2_in_clip_space.y  * 0.5 + 0.5, 0.0, 1.0),
            vertex_2_in_clip_space.z  * 0.5 + 0.5);

    std::vector<CommonMath::Vec3> vertices_in_uv_space {
            CommonMath::Vec3(vertex_0_in_normalized_device_space.x, vertex_0_in_normalized_device_space.y, vertex_0_in_normalized_device_space.z),
            CommonMath::Vec3(vertex_1_in_normalized_device_space.x, vertex_1_in_normalized_device_space.y, vertex_1_in_normalized_device_space.z),
            CommonMath::Vec3(vertex_2_in_normalized_device_space.x, vertex_2_in_normalized_device_space.y, vertex_2_in_normalized_device_space.z),
    };

    rec.u = (vertices_in_uv_space[0].x() * alpha) +
            (vertices_in_uv_space[1].x() * beta) +
            (vertices_in_uv_space[2].x() * gamma);

    rec.v = (vertices_in_uv_space[0].y() * alpha) +
            (vertices_in_uv_space[1].y() * beta) +
            (vertices_in_uv_space[2].y() * gamma);

    rec.t = appropriate_direction_scaler;
    rec.p = intersection_point;
    rec.mat_ptr = this->mat_ptr;
    rec.set_face_normal(r, this->normal);

    return true;
}
