#pragma once

#include "interval.h"
#include "common_math/vec3.h"
#include "common_math/ray.h"

class AABB{
public:
    Interval x = Interval(0, 0), y = Interval(0, 0), z = Interval(0, 0);

    AABB() = default;

    AABB(Interval& intervalX, Interval& intervalY, Interval& intervalZ)
        : x(intervalX), y(intervalY), z(intervalZ){};

    AABB(const CommonMath::Point3& pointA, const CommonMath::Point3& pointB);

    AABB(AABB box1,AABB box2);

    const Interval& axis(int n) const;
    bool hit(const CommonMath::Ray& r,Interval& ray_t) const;

    AABB expand_box_on_small_delta_if_needed() const;
};