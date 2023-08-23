#include "aabb.h"
#include "interval.h"


AABB::AABB(const Point3 &pointA, const Point3 &pointB) {
    this->x = Interval(fmin(pointA[0], pointB[0]), fmax(pointA[0], pointA[0]));
    this->y = Interval(fmin(pointA[1], pointB[1]), fmax(pointA[1], pointA[1]));
    this->z = Interval(fmin(pointA[2], pointB[2]), fmax(pointA[2], pointA[2]));
}

const Interval& AABB::axis(int n) const {
    if (n == 0){
        return x;
    }

    if (n == 1){
        return y;
    }

    return z;
}

bool AABB::hit(const Ray &r, Interval &ray_t) const {
    for (int a = 0;a < 3;a++){
        double invD = 1 / r.GetDirection()[a];
        double origin = r.GetOrigin()[a];

        double t0 = (this->axis(a).min - origin) * invD;
        double t1 = (this->axis(a).max - origin) * invD;

        if (invD < 0){
            std::swap(t0, t1);
        }

        if (t0 > ray_t.min) ray_t.min = t0;
        if (t1 < ray_t.max) ray_t.max = t1;

        if (ray_t.max <= ray_t.min){
            return false;
        }
    }

    return true;
}