#pragma once

#include "../hittable.h"
#include "placeable_on_plane.h"

class Triangle: public Hittable, public PlaceableOnPlane{
private:
    CommonMath::Point3 vertexA;
    CommonMath::Point3 vertexB;

    CommonMath::Vec3 AB;
    CommonMath::Vec3 BC;

    CommonMath::Vec3 v_vector_for_barycentric_alpha;
    CommonMath::Vec3 v_vector_for_barycentric_beta;

    std::shared_ptr<Material> mat_ptr;

public:
    Triangle(
            CommonMath::Point3 vertexA,
            CommonMath::Point3 vertexB,
            CommonMath::Point3 vertexC,
            std::shared_ptr<Material> _mat_ptr);

    AABB get_bounding_box() const override;

    bool hit(const CommonMath::Ray& r, Interval ray_t, hit_record& rec) const override;
};

