#pragma once

#include "common_math/random.h"
#include "common_math/vec3.h"
#include "common_math/ray.h"
#include "interval.h"
#include "aabb.h"
#include <memory>

class Material;


struct hit_record{
    CommonMath::Point3 p = CommonMath::Point3(0.0f, 0.0f, 0.0f);
    CommonMath::Vec3 normal = CommonMath::Vec3(0.0f, 0.0f, 0.0f);
    std::shared_ptr<Material> mat_ptr;

    double t = 0.0f;
    bool front_face = false;
    double u, v;

    inline void set_face_normal(const CommonMath::Ray& r, CommonMath::Vec3 outward_normal){
        front_face = dot(r.GetDirection(), outward_normal) < 0;
        normal = front_face ? outward_normal: -outward_normal;
    }
};


class Hittable{
public:
    virtual bool hit(const CommonMath::Ray& r, Interval ray_t, hit_record& rec) const = 0;

    virtual AABB get_bounding_box() const = 0;
};
