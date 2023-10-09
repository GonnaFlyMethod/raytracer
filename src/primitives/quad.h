#pragma once

#include "../material.h"
#include "../aabb.h"
#include "../common_math/vec3.h"
#include "../common_math/ray.h"
#include "placeable_on_plane.h"


class Quad: public Hittable, public PlaceableOnPlane {
private:
    std::shared_ptr<Material> mat_ptr;
    CommonMath::Vec3 constant_vec_for_finding_alpha_beta;

public:
    Quad(CommonMath::Point3 q, CommonMath::Vec3 _u, CommonMath::Vec3 _v, std::shared_ptr<Material> _mat_ptr);
    AABB get_bounding_box() const override;

    virtual bool hit(const CommonMath::Ray& r, Interval ray_t, hit_record& rec) const override;
};
