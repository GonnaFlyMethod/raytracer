#pragma once

#include "common.h"

class Material;


struct hit_record{
    Point3 p = Point3(0.0f, 0.0f, 0.0f);
    Vec3 normal = Vec3(0.0f, 0.0f, 0.0f);
    shared_ptr<Material> mat_ptr;

    double t = 0.0f;
    bool front_face = false;

    inline void set_face_normal(const Ray& r, Vec3& outward_normal){
        front_face = dot(r.GetDirection(), outward_normal) < 0;
        normal = front_face ? outward_normal: -outward_normal;
    }
};


class Hittable{
public:
    virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};
