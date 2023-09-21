#include "bvh.h"
#include "common_math/random.h"
#include "common_math/ray.h"
#include "aabb.h"

BoundingVolumeNode::BoundingVolumeNode(const std::vector<std::shared_ptr<Hittable>> &src_objects, size_t start, size_t end) {
    auto objects = src_objects;

    int axis = CommonMath::random_int(0, 2);
    auto comparator = (axis == 0) ? box_x_compare:
                      (axis == 1) ? box_y_compare:
                      box_z_compare;

    size_t object_span = end - start;

    if (object_span == 1){
        this->left = this->right = objects[start];
    }else if (object_span == 2){
        if (comparator(objects[start], objects[start+1])){
            this->left = objects[start];
            this->right = objects[start+1];
        }else{
            this->left = objects[start+1];
            this->right = objects[start];
        }
    }else{
        // TODO: remove addition of start in the 1st argument
        std::sort(objects.begin() + start,
                  objects.begin() + end, comparator);

        auto mid = start + object_span / 2;

        this->left = std::make_shared<BoundingVolumeNode>(objects, start,mid);
        this->right = std::make_shared<BoundingVolumeNode>(objects, mid, end);
    }

    this->bounding_box = AABB(
            this->left->get_bounding_box(),
            this->right->get_bounding_box());
}

bool BoundingVolumeNode::hit(const CommonMath::Ray &r, Interval ray_t, hit_record &rec) const {
    if (!this->bounding_box.hit(r, ray_t)){
        return false;
    }

    bool hit_left = this->left->hit(r, ray_t, rec);
    bool hit_right = this->right->hit(r,Interval(ray_t.min, hit_left ? rec.t : ray_t.max), rec);

    return hit_left || hit_right;
}

AABB BoundingVolumeNode::get_bounding_box() const {return bounding_box;}

bool BoundingVolumeNode::axis_compare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b, int axis_index){
    return a->get_bounding_box().axis(axis_index).min < b->get_bounding_box().axis(axis_index).min;
}

bool BoundingVolumeNode::box_x_compare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b) {
    return BoundingVolumeNode::axis_compare(a, b, 0);
}

bool BoundingVolumeNode::box_y_compare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b) {
    return BoundingVolumeNode::axis_compare(a, b, 1);
}

bool BoundingVolumeNode::box_z_compare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b) {
    return BoundingVolumeNode::axis_compare(a, b, 2);
}