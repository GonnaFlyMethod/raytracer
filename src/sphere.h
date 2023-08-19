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

bool Sphere::hit(const Ray& r, double t_min, double t_max, hit_record& rec) const{
    Vec3 cr = r.GetOrigin() - this->center;

    double a = r.GetDirection().length_squared();
    double half_b = dot(cr, r.GetDirection());
    double c = cr.length_squared() - this->radius * this->radius;

    double discriminant = half_b * half_b - a*c;

    if (discriminant < 0){
        return false;
    }

    double root = (-half_b - sqrt(discriminant) ) / a;

    if (root < t_min || root > t_max){
        root = (-half_b + sqrt(discriminant) ) / a;

        if (root < t_min || root > t_max){
            return false;
        }
    }

    rec.t = root;
    rec.p = r.at(rec.t);

    Vec3 outward_normal = (rec.p - this->center) / this->radius;

    rec.set_face_normal(r, outward_normal);

    rec.mat_ptr = this->mat_ptr;

    return true;
}
