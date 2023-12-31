#include "aabb.h"
#include "interval.h"
#include "common_math/vec3.h"
#include "common_math/ray.h"


AABB::AABB(const CommonMath::Point3 &pointA, const CommonMath::Point3 &pointB) {
    this->x = Interval(fmin(pointA[0], pointB[0]), fmax(pointA[0], pointB[0]));
    this->y = Interval(fmin(pointA[1], pointB[1]), fmax(pointA[1], pointB[1]));
    this->z = Interval(fmin(pointA[2], pointB[2]), fmax(pointA[2], pointB[2]));
}

AABB::AABB(AABB box1, AABB box2) {
    this->x = Interval(box1.x, box2.x);
    this->y = Interval(box1.y, box2.y);
    this->z = Interval(box1.z, box2.z);
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

bool AABB::hit(const CommonMath::Ray &r, Interval &ray_t) const {
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

AABB AABB::expand_box_on_small_delta_if_needed() const {
    double delta = 0.0001f;

    Interval new_x = this->x.size() >= delta ? this->x : this->x.expand(delta);
    Interval new_y = this->y.size() >= delta ? this->y : this->y.expand(delta);
    Interval new_z = this->z.size() >= delta ? this->z : this->z.expand(delta);

    return {new_x, new_y, new_z};
}
