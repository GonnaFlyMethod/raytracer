#include "placeable_on_plane.h"

PlaceableOnPlane::PlaceableOnPlane(CommonMath::Point3 q, CommonMath::Vec3 u, CommonMath::Vec3 v) {
    this->q_point = q;
    this->u = u;
    this->v = v;

    this->normal = unit_vector(CommonMath::cross(u,v));
    this->constant_in_plane_equation = dot(this->normal,  this->q_point);

    this->box = AABB(q, q + u + v).expand_box_on_small_delta_if_needed();
}

bool PlaceableOnPlane::does_hit_plane(const CommonMath::Ray &r, Interval ray_t, double& appropriate_direction_scaler) const {
    // checking whether direction of the ray is OK
    double denominator = CommonMath::dot(this->normal, r.GetDirection());

    if (fabs(denominator) < 1e-8){
        return false;
    }

    // checking whether direction scaler of the ray is OK
    appropriate_direction_scaler = (this->constant_in_plane_equation - CommonMath::dot(this->normal, r.GetOrigin())) / denominator;

    if (!ray_t.contains(appropriate_direction_scaler)){
        return false;
    }

    return true;
}