#pragma once

#include "interval.h"
#include "vec3.h"
#include "ray.h"

class AABB{
public:
    Interval x = Interval(0, 0), y = Interval(0, 0), z = Interval(0, 0);

    AABB() = default;

    AABB(Interval& intervalX, Interval& intervalY, Interval& intervalZ)
        : x(intervalX), y(intervalY), z(intervalZ){};

    AABB(const Point3& pointA, const Point3& pointB);

    AABB(AABB& box1,AABB box2);

    const Interval& axis(int n) const;

    bool hit(const Ray& r,Interval& ray_t) const;
};