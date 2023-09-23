#include "quad.h"

Quad::Quad(
        CommonMath::Point3 q,
        CommonMath::Vec3 u,
        CommonMath::Vec3 v,
        std::shared_ptr<Material> _mat_ptr): PlaceableOnPlane(q,u,v), mat_ptr(_mat_ptr) {

    CommonMath::Vec3 n = cross(u, v);
    this->constant_vec_for_finding_alpha_beta = n / CommonMath::dot(n, n);
}

AABB Quad::get_bounding_box() const {
    return this->box;
}

bool Quad::hit(const CommonMath::Ray &r, Interval ray_t, hit_record &rec) const {
    double appropriate_direction_scaler;

    if (!this->does_hit_plane(r, ray_t, appropriate_direction_scaler)){
        return false;
    }

    CommonMath::Point3 intersection_point = r.at(appropriate_direction_scaler);
    CommonMath::Vec3 quad_hit_vec = intersection_point - this->q_point;

    double alpha = CommonMath::dot(this->constant_vec_for_finding_alpha_beta, CommonMath::cross(quad_hit_vec, this->v));
    double beta = CommonMath::dot(this->constant_vec_for_finding_alpha_beta, CommonMath::cross(this->u, quad_hit_vec));

    if(alpha < 0 || alpha > 1 || beta < 0 || beta > 1){
        return false;
    }

    rec.u = alpha;
    rec.v = beta;

    rec.t = appropriate_direction_scaler;
    rec.p = intersection_point;
    rec.mat_ptr = this->mat_ptr;
    rec.set_face_normal(r, this->normal);

    return true;
}