#include <algorithm>
#include "triangle.h"


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
//
//     rec.u = intersection_point.x() - this->box.x.min / (this->box.x.max - this->box.x.min);
//     rec.v = intersection_point.y() - this->box.y.min / (this->box.y.max - this->box.y.min);

    std::vector<double> vertices_in_clipspace[3]{
            this->cam.convert_to_clip_space_coords(vertex0),
            this->cam.convert_to_clip_space_coords(vertex1),
            this->cam.convert_to_clip_space_coords(vertex2),
    };

    // Normalizing clip space coordinates
    for(int i = 0;i < 3;i++){
        for (int j = 0; j < 3; j++){
            vertices_in_clipspace[i][j] /= vertices_in_clipspace[i][3];
        }
    }



    std::vector<CommonMath::Vec3> vertices_in_uv_space;

    for(std::vector<double> clipspace_vertex: vertices_in_clipspace){
        CommonMath::Vec3 vertex_in_uv_space = CommonMath::Vec3(
                clipspace_vertex[0] * 0.5 +0.5,
                clipspace_vertex[1] * 0.5 +0.5,
                0.0f);

        vertices_in_uv_space.push_back(vertex_in_uv_space);
    }

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

    // TODO: finilize and explain the stretching of square texture during the process of blending between
    //  uv coordinates of triangle's vertices_in_clipspace

//    rec.u = uv_coords[0][0] * barycentric_coordinates_of_vertices[0] +
//            uv_coords[1][0] * barycentric_coordinates_of_vertices[1] +
//            uv_coords[2][0] * barycentric_coordinates_of_vertices[2];
//
//    rec.v = uv_coords[0][1] * barycentric_coordinates_of_vertices[0] +
//            uv_coords[1][1] * barycentric_coordinates_of_vertices[1] +
//            uv_coords[2][1] * barycentric_coordinates_of_vertices[2];

    // Push vectors to uv_coords, us barycentric coordinates and uv coordinates of each vertex of triangle
    // to calculate true uv for ray-triangle intersection point


//    CommonMath::Vec3 vec_from_q_point_to_intersection_point = intersection_point - this->q_point;
//    CommonMath::Vec3 projected_vector_onto_u = CommonMath::project(
//            vec_from_q_point_to_intersection_point, this->u);
//
//    rec.u = projected_vector_onto_u.length() / this->u.length();
//
//    CommonMath::Vec3 projected_vector_onto_v = CommonMath::project(
//            vec_from_q_point_to_intersection_point, this->v);
//
//    rec.v = projected_vector_onto_v.length() / this->v.length();

    rec.t = appropriate_direction_scaler;
    rec.p = intersection_point;
    rec.mat_ptr = this->mat_ptr;
    rec.set_face_normal(r, this->normal);

    return true;
}
