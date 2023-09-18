#include "quad.h"

Quad::Quad(CommonMath::Point3 q, CommonMath::Vec3 _u, CommonMath::Vec3 _v): q_point(q), u(_u), v(_v), mat_ptr(mat_ptr) {
    CommonMath::Vec3 n = cross(u, v);
    this->normal = unit_vector(n);
    this->constant_in_plane_equation = dot(q,  normal);

    this->box = AABB(q, q + u + v).expand_box_on_small_delta_if_needed();
}

AABB Quad::get_bounding_box() const {
    return this->box;
}

bool Quad::hit(const CommonMath::Ray &r, Interval ray_t, hit_record &rec) const {
    // checking whether direction of the ray is OK
    double denominator = dot(this->normal, r.GetDirection());

    if (fabs(denominator) < 1e-8){
        return false;
    }

    // checking whether direction scaler of the ray is OK
    double appropriate_direction_scaler = (
            this->constant_in_plane_equation - dot(this->normal, r.GetOrigin())) / denominator;

    if (!ray_t.contains(appropriate_direction_scaler)){
        return false;
    }

    CommonMath::Point3 intersection_point = r.at(appropriate_direction_scaler);

    rec.t = appropriate_direction_scaler;
    rec.p = intersection_point;
    rec.mat_ptr = this->mat_ptr;
    rec.set_face_normal(r, this->normal);

    return true;
}