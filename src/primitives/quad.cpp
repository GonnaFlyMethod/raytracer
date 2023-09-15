#include "quad.h"

Quad::Quad(Point3 q, Vec3 _u, Vec3 _v): q_point(q), u(_u), v(_v), mat(mat) {
    this->box = AABB(q, q + u + v).expand_box_on_small_delta_if_needed();
}

AABB Quad::get_bounding_box() const {
    return this->box;
}

bool Quad::hit(const Ray &r, Interval ray_t, hit_record &rec) const {
    return false; // To be implemented
}