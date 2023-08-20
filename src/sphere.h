#pragma once

#include "hittable.h"

class Sphere: public Hittable{
public:
    Point3  center;
    double radius;
    shared_ptr<Material> mat_ptr;

    Sphere(Point3 cen, double r, shared_ptr<Material> m): center(cen), radius(r), mat_ptr(m) {};

    virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const override;
};
