#pragma once

#include "../hittable.h"

class Triangle: public Hittable{
    bool hit(const CommonMath::Ray& r, Interval ray_t, hit_record& rec) const override;

    AABB get_bounding_box() const override;
};

