# pragma once

#include "../common_math/vec3.h"
#include "../aabb.h"

class PlaceableOnPlane {
private:
    double constant_in_plane_equation;
protected:
    AABB box;
    CommonMath::Point3 q_point;
    CommonMath::Vec3 normal;
    CommonMath::Vec3 u, v;

    bool does_hit_plane(const CommonMath::Ray &r, Interval ray_t, double& appropriate_direction_scaler) const;
public:
    PlaceableOnPlane(CommonMath::Point3 q, CommonMath::Vec3 _u, CommonMath::Vec3 _v);
};

