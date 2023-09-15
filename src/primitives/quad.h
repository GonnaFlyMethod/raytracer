#pragma once

#include "../vec3.h"
#include "../material.h"


class Quad: public Hittable {
private:
    Point3 q_point;
    Vec3 u, v;
    std::shared_ptr<Material> mat;
    AABB box;

public:
    Quad(Point3 q, Vec3 _u, Vec3 _v);
    AABB get_bounding_box() const override;

    virtual bool hit(const Ray& r, Interval ray_t, hit_record& rec) const = 0;
};
