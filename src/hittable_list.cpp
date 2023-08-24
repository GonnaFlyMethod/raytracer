#include "hittable_list.h"

using std::shared_ptr;
using std::make_shared;

HittableList::HittableList(std::shared_ptr<Hittable> hittable_object){
    this->add(hittable_object);
}

AABB HittableList::get_bounding_box() const{
    return this->bounding_box;
}

void HittableList::add(std::shared_ptr<Hittable> hittable_object) {
    this->objects.push_back(hittable_object);
    this->bounding_box = AABB(this->bounding_box, hittable_object->get_bounding_box());
}

void HittableList::clear(){
    this->objects.clear();
}

bool HittableList::hit(const Ray &r, double t_min, double t_max, hit_record &rec) const {
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
