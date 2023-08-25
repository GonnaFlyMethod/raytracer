#include "bvh.h"

BoundingVolumeNode::BoundingVolumeNode(const std::vector<shared_ptr<Hittable>> &src_objects, size_t start, size_t end) {

}

bool BoundingVolumeNode::hit(const Ray &r, Interval ray_t, hit_record &rec) const {
    if (!this->bounding_box.hit(r, ray_t)){
        return false;
    }

    bool hit_left = this->left->hit(r, ray_t, rec);
    bool hit_right = right->hit(r,Interval(ray_t.min, hit_left ? rec.t : ray_t.max), rec);

    return hit_left || hit_right;
}
