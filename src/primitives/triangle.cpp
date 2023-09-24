#include <algorithm>
#include "triangle.h"


PlaceableOnPlane
Triangle::construct_correct_uv(CommonMath::Point3 vertexA, CommonMath::Point3 vertexB, CommonMath::Point3 vertexC) {
    std::vector<CommonMath::Point3> vertices{vertexA, vertexB, vertexC};

    std::ranges::sort(vertices, [](const CommonMath::Point3& a, const CommonMath::Point3& b){
        return a.x() < b.x();
    });

    int q_point_index;

    if (vertices[0].x() == vertices[1].x()){
        q_point_index = vertices[0].y() < vertices[1].y() ? 0 : 1;
    }else{
        q_point_index = 0;
    }

    CommonMath::Point3 q_point = vertices[q_point_index];
    vertices.erase(vertices.begin() + q_point_index);

    int v_index;

    if (vertices[0].y() > vertices[1].y()){
        v_index = 0;
    }else{
        v_index = 1;
    }

    CommonMath::Vec3 v = vertices[v_index];
    vertices.erase(vertices.begin() + v_index);

    CommonMath::Vec3 u = vertices[0];

    return {q_point, u, v};
}

Triangle::Triangle(
        CommonMath::Point3 vertexA,
        CommonMath::Point3 vertexB,
        CommonMath::Point3 vertexC,
        std::shared_ptr<Material> _mat_ptr)
    : PlaceableOnPlane(construct_correct_uv(vertexA, vertexB, vertexC)), mat_ptr(_mat_ptr) {

    this->vertexA = vertexA;
    this->AB = vertexB - vertexA;
    CommonMath::Vec3 CB = vertexB - vertexC;

    this->v_vector_for_barycentric_alpha = this->AB - CommonMath::project(this->AB, CB);

    this->vertexB = vertexB;
    this->BC = vertexB - vertexC;
    CommonMath::Vec3 AC = vertexA - vertexC;

    this->v_vector_for_barycentric_beta = this->BC - CommonMath::project(this->BC, AC);
}

AABB Triangle::get_bounding_box() const {
    return this->box;
}

bool Triangle::hit(const CommonMath::Ray &r, Interval ray_t, hit_record &rec) const {
// TODO: try to replace the current code for alpa, beta and gamma on this one:
//    d1 = get_distance(p, a);
//    d2 = get_distance(p, b);
//    d3 = get_distance(p, c);

//    r1 = d1 / (d1 + d2 + d3); aka alpha
//    r2 = d2 / (d1 + d2 + d3); aka beta
//    r3 = d3 / (d1 + d2 + d3); aka gamma

    double appropriate_direction_scaler;

    if (!this->does_hit_plane(r, ray_t, appropriate_direction_scaler)){
        return false;
    }

    CommonMath::Point3 intersection_point = r.at(appropriate_direction_scaler);

     double alpha = 1.0f - (
             dot(intersection_point - this->vertexA, this->v_vector_for_barycentric_alpha) /
             dot(this->AB, this->v_vector_for_barycentric_alpha));

     double beta = 1.0f - (
             dot(intersection_point - this->vertexB, this->v_vector_for_barycentric_beta) /
             dot(this->BC, this->v_vector_for_barycentric_beta));

     double gamma = 1.0f - alpha - beta;

     if (alpha < 0.0f || beta < 0.0f || gamma < 0.0f){
         return false;
     }

     // TODO: remap barycentric coordinates to uv coordinates;
     // https://plugincafe.maxon.net/topic/9630/12933_convert-barycentric-coords-to-uv-coords/2
     // https://stackoverflow.com/questions/23980748/triangle-texture-mapping-with-barycentric-coordinates
     // https://computergraphics.stackexchange.com/questions/1866/how-to-map-square-texture-to-triangle

     rec.u = intersection_point.x() - this->box.x.min / this->box.x.max - this->box.x.min;
     rec.v = intersection_point.x() - this->box.y.min / this->box.y.max - this->box.y.min;

     rec.t = appropriate_direction_scaler;
     rec.p = intersection_point;
     rec.mat_ptr = this->mat_ptr;
     rec.set_face_normal(r, this->normal);

    return true;
}
