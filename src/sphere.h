#pragma once

#include "hittable.h"

class Sphere: public Hittable{
private:
    Point3 center1;

    Vec3 blending_vec_to_center2;

    bool is_moving;

    double radius;
    shared_ptr<Material> mat_ptr;

    AABB bounding_box;

    Point3 center(double time) const;

public:
    // Stationary sphere
    Sphere(Point3 cen, double r, shared_ptr<Material> m);

    // Moving sphere
    Sphere(Point3 cen1, Point3 cen2, double r, shared_ptr<Material> m);

    virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const override;

    virtual AABB get_bounding_box() const override;
};
