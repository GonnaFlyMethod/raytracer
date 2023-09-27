#pragma once

#include "../hittable.h"
#include "placeable_on_plane.h"

class Triangle: public Hittable, public PlaceableOnPlane{
private:
    CommonMath::Point3 vertex0;
    CommonMath::Point3 vertex1;
    CommonMath::Point3 vertex2;

    CommonMath::Vec3 vertex0_vertex1_edge;
    CommonMath::Vec3 vertex1_vertex2_edge;
    CommonMath::Vec3 vertex2_vertex0_edge;

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

