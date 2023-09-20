#pragma once

#include "material.h"
#include "aabb.h"
#include "common_math/vec3.h"
#include "common_math/ray.h"


class Quad: public Hittable {
private:
    CommonMath::Point3 q_point;
    CommonMath::Vec3 u, v;
    std::shared_ptr<Material> mat_ptr;
    AABB box;

    CommonMath::Vec3 normal;
    double constant_in_plane_equation;

    CommonMath::Vec3 constant_vec_for_finding_alpha_beta;

public:
    Quad(CommonMath::Point3 q, CommonMath::Vec3 _u, CommonMath::Vec3 _v);
    AABB get_bounding_box() const override;

    virtual bool hit(const CommonMath::Ray& r, Interval ray_t, hit_record& rec) const = 0;
};
