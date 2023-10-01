#include <algorithm>
#include "triangle.h"
#include "../external/glm/glm.hpp"
#include "../external/glm/ext/matrix_transform.hpp"
#include "../external/glm/ext/matrix_clip_space.hpp"


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

    CommonMath::Vec3 vertex0_intersection_point_vec = intersection_point - vertex0;

    CommonMath::Vec3 C0 = cross(vertex0_vertex1_edge, vertex0_intersection_point_vec);
    bool is_intersection_point_on_left_side_of_edge = dot(this->normal, C0) > 0;

    if (!is_intersection_point_on_left_side_of_edge){
        return false;
    }

    CommonMath::Vec3 vertex1_intersection_point_vec = intersection_point - vertex1;
    CommonMath::Vec3 C1 = cross(vertex1_vertex2_edge, vertex1_intersection_point_vec);

    is_intersection_point_on_left_side_of_edge = dot(this->normal, C1) > 0;
    if (!is_intersection_point_on_left_side_of_edge){
        return false;
    }

    CommonMath::Vec3 vertex2_intersection_point_vec = intersection_point - vertex2;
    CommonMath::Vec3 C2 = cross(vertex2_vertex0_edge, vertex2_intersection_point_vec);

    is_intersection_point_on_left_side_of_edge = dot(this->normal, C2) > 0;
    if (!is_intersection_point_on_left_side_of_edge){
        return false;
    }

     // TODO: remap barycentric coordinates to uv coordinates;
     // https://plugincafe.maxon.net/topic/9630/12933_convert-barycentric-coords-to-uv-coords/2
     // https://stackoverflow.com/questions/23980748/triangle-texture-mapping-with-barycentric-coordinates
     // https://computergraphics.stackexchange.com/questions/1866/how-to-map-square-texture-to-triangle

    // TODO: finilize and explain the stretching of square texture during the process of blending between
    //  uv coordinates of triangle's vertices using barycentric weights


    // TODO: Now the texture maps to the triangle without wierd stretching but the orientation of
    // vertices in uv space is incorrect. Find out why and fix that. Pro-tip: it's good to make triangle
    // bigger so in this case I can observe the larger amount of texture and I then I can check whether
    // the orientation of vertices are correct. (Find out why 0.6 in uv space does not represent the same height in the texture space)

    // TODO: !!! I should not map just to uv coordinates of screen [0;1] but map to coordinates of the texture [0;1]

    glm::mat4 viewMatrix = glm::mat4(1.0f);
//    viewMatrix = glm::translate(viewMatrix,
//                                -glm::vec3(cam.lookfrom.x(), cam.lookfrom.y(), cam.lookfrom.z());
    viewMatrix = glm::lookAt(glm::vec3(cam.lookfrom.x(), cam.lookfrom.y(), cam.lookfrom.z()),
                glm::vec3(cam.lookat.x(), cam.lookat.y(), cam.lookat.z()), glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 projectionMatrix = glm::perspective(
            glm::radians(cam.vfov), (double)cam.aspect_ratio, 0.0, 1000.0);


    glm::vec4 vertex_0_in_clip_space = projectionMatrix * viewMatrix * glm::vec4(vertex0.x(), vertex0.y(), vertex0.z(), 1.0f);
    glm::vec4 vertex_1_in_clip_space = projectionMatrix * viewMatrix * glm::vec4(vertex1.x(), vertex1.y(), vertex1.z(), 1.0f);
    glm::vec4 vertex_2_in_clip_space = projectionMatrix * viewMatrix * glm::vec4(vertex2.x(), vertex2.y(), vertex2.z(), 1.0f);

    glm::vec3 vertex_0_in_normalized_device_space = glm::vec3(
            (vertex_0_in_clip_space.x / vertex_0_in_clip_space.w) * 0.5f + 0.5f,
            (vertex_0_in_clip_space.y / vertex_0_in_clip_space.w) * 0.5f + 0.5f,
            (vertex_0_in_clip_space.z / vertex_0_in_clip_space.w) * 0.5f + 0.5f);

    glm::vec3 vertex_1_in_normalized_device_space = glm::vec3(
            (vertex_1_in_clip_space.x / vertex_1_in_clip_space.w) * 0.5f + 0.5f,
            (vertex_1_in_clip_space.y / vertex_1_in_clip_space.w) * 0.5f + 0.5f,
            (vertex_1_in_clip_space.z / vertex_1_in_clip_space.w) * 0.5f + 0.5f);

    glm::vec3 vertex_2_in_normalized_device_space = glm::vec3(
            (vertex_2_in_clip_space.x / vertex_2_in_clip_space.w) * 0.5f + 0.5f,
            (vertex_2_in_clip_space.y / vertex_2_in_clip_space.w) * 0.5f + 0.5f,
            (vertex_2_in_clip_space.z / vertex_2_in_clip_space.w) * 0.5f + 0.5f);


//    // Normalizing clip space coordinates
//    for(int i = 0;i < 3;i++){
//        for (int j = 0; j < 3; j++){
//            vertices_in_clipspace[i][j] /= vertices_in_clipspace[i][3];
//        }
//    }

    std::vector<CommonMath::Vec3> vertices_in_uv_space {
        CommonMath::Vec3(vertex_0_in_normalized_device_space.x, vertex_0_in_normalized_device_space.y, vertex_0_in_normalized_device_space.z),
        CommonMath::Vec3(vertex_1_in_normalized_device_space.x, vertex_1_in_normalized_device_space.y, vertex_1_in_normalized_device_space.z),
        CommonMath::Vec3(vertex_2_in_normalized_device_space.x, vertex_2_in_normalized_device_space.y, vertex_2_in_normalized_device_space.z),
    };

    double a_side_of_whole_triangle = this->vertex0_vertex1_edge.length();
    double b_side_of_whole_triangle = this->vertex1_vertex2_edge.length();
    double c_side_of_whole_triangle = this->vertex2_vertex0_edge.length();

    double semi_perimeter = (a_side_of_whole_triangle + b_side_of_whole_triangle + c_side_of_whole_triangle) / 2.0f;

    double area_of_whole_triangle =
        sqrt(semi_perimeter * (semi_perimeter - a_side_of_whole_triangle) *
            (semi_perimeter - b_side_of_whole_triangle) *
            (semi_perimeter - c_side_of_whole_triangle));

    // V1PV2 sub triangle
    double v1_p_a_side = (intersection_point - vertex1).length();
    double v2_p_b_side = (intersection_point - vertex2).length();
    double v1_p_v2_semi_perimeter = (v1_p_a_side + v2_p_b_side + b_side_of_whole_triangle) / 2.0f;

    double v1_p_v2_area = sqrt(v1_p_v2_semi_perimeter *
                               (v1_p_v2_semi_perimeter - v1_p_a_side) *
                               (v1_p_v2_semi_perimeter - v2_p_b_side) *
                               (v1_p_v2_semi_perimeter - b_side_of_whole_triangle));

    double alpha = v1_p_v2_area / area_of_whole_triangle;

    // V1PV2 sub triangle
    double v0_p_a_side = (intersection_point - vertex0).length();
    v2_p_b_side = (intersection_point - vertex2).length();
    double v2_p_v0_semi_perimeter = (v0_p_a_side + v2_p_b_side + c_side_of_whole_triangle) / 2.0f;

    double v2_p_v0_area = sqrt(v2_p_v0_semi_perimeter *
                               (v2_p_v0_semi_perimeter - v0_p_a_side) *
                               (v2_p_v0_semi_perimeter - v2_p_b_side) *
                               (v2_p_v0_semi_perimeter - c_side_of_whole_triangle));

    double beta = v2_p_v0_area / area_of_whole_triangle;

    // V0PV1 sub triangle
    v0_p_a_side = (intersection_point - vertex0).length();
    double v1_p_b_side = (intersection_point - vertex1).length();
    double v0_p_v1_semi_perimeter = (v0_p_a_side + v1_p_b_side + a_side_of_whole_triangle) / 2.0f;

    double v0_p_v1_area = sqrt(v0_p_v1_semi_perimeter *
            (v0_p_v1_semi_perimeter - v0_p_a_side) *
            (v0_p_v1_semi_perimeter - v1_p_b_side) *
            (v0_p_v1_semi_perimeter - a_side_of_whole_triangle));

    double gamma = v0_p_v1_area / area_of_whole_triangle;

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
