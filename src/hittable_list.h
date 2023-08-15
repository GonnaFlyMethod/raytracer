#pragma once

#include "hittable.h"
#include "memory"
#include "vector"

using std::shared_ptr;
using std::make_shared;

class HittableList: public Hittable  {
public:
     std::vector<std::shared_ptr<Hittable>> objects;

     HittableList() = default;
     explicit HittableList(std::shared_ptr<Hittable> hittable_object) { this->add(hittable_object);}

     void add(std::shared_ptr<Hittable> hittable_object){
         this->objects.push_back(hittable_object);
     }

     void clear(){
         this->objects.clear();
     }

    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

};

bool HittableList::hit(const ray &r, double t_min, double t_max, hit_record &rec) const {
    hit_record tmp_record;

    bool hitted_some_object = false;
    double closest_so_far = t_max;

    for(const auto& object: objects){
        if (object->hit(r, t_min, closest_so_far, tmp_record)){
            hitted_some_object = true;
            closest_so_far = tmp_record.t;
            rec = tmp_record;
        }
    }

    return hitted_some_object;
}