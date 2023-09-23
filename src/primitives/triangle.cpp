#include "triangle.h"


Triangle::Triangle(
        CommonMath::Point3 vertexA,
        CommonMath::Point3 vertexB,
        CommonMath::Point3 vertexC,
        std::shared_ptr<Material> _mat_ptr)
    : PlaceableOnPlane(vertexA, vertexB- vertexA, vertexC - vertexA), mat_ptr(_mat_ptr) {

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

     rec.t = appropriate_direction_scaler;
     rec.p = intersection_point;
     rec.mat_ptr = this->mat_ptr;
     rec.set_face_normal(r, this->normal);

    return false; // To be implemented
}