#pragma once

#include "hittable.h"
#include "memory"
#include "vector"

class HittableList: public Hittable  {
public:
     std::vector<std::shared_ptr<Hittable>> objects;

     HittableList() = default;
     explicit HittableList(std::shared_ptr<Hittable> hittable_object);

     void add(std::shared_ptr<Hittable> hittable_object);

     void clear();

    virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const override;
};