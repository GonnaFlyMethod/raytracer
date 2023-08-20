#pragma once

#include "hittable.h"

class Sphere: public Hittable{
private:
    Point3 center1;

    Vec3 blending_vec_to_center2;

    bool is_moving;

    double radius;
    shared_ptr<Material> mat_ptr;

    Point3 center(double time) const;

public:
    // Stationary sphere
    Sphere(Point3 cen, double r, shared_ptr<Material> m): center1(cen), radius(r), mat_ptr(m) {};

    // Moving sphere
    Sphere(Point3 cen1, Point3 cen2, double r, shared_ptr<Material> m)
        : center1(cen1),
        radius(r),
        mat_ptr(m),
        is_moving(true),
        blending_vec_to_center2(cen2 - cen1){};

    virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const override;
};
