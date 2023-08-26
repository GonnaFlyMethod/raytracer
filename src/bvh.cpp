#include "bvh.h"
#include "common_math.h"

BoundingVolumeNode::BoundingVolumeNode(const std::vector<shared_ptr<Hittable>> &src_objects, size_t start, size_t end) {
    auto objects = src_objects;

    int axis = random_double(0, 2);
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
        auto objects_iterator = objects.begin();
        // TODO: remove addition of start in the 1st argument
        std::sort(objects_iterator, objects_iterator + end, comparator);

        auto mid = start + object_span / 2;
        this->left = make_shared<BoundingVolumeNode>(objects, start,mid);
        this->right = make_shared<BoundingVolumeNode>(objects, mid, end);
    }

    this->bounding_box = AABB(
            this->left->get_bounding_box(),
            this->right->get_bounding_box());
}

bool BoundingVolumeNode::hit(const Ray &r, Interval ray_t, hit_record &rec) const {
    if (!this->bounding_box.hit(r, ray_t)){
        return false;
    }

    // Actual hits of spheres
    bool hit_left = this->left->hit(r, ray_t, rec);
    bool hit_right = right->hit(r,Interval(ray_t.min, hit_left ? rec.t : ray_t.max), rec);

    return hit_left || hit_right;
}

AABB BoundingVolumeNode::get_bounding_box() const {return bounding_box;}

bool BoundingVolumeNode::axis_compare(const shared_ptr<Hittable> a, const shared_ptr<Hittable> b, int axis){
    return a->get_bounding_box().axis(axis).min < b->get_bounding_box().axis(axis).min;
}

bool BoundingVolumeNode::box_x_compare(const shared_ptr<Hittable> a, const shared_ptr<Hittable> b) {
    return BoundingVolumeNode::axis_compare(a, b, 0);
}

bool BoundingVolumeNode::box_y_compare(const shared_ptr<Hittable> a, const shared_ptr<Hittable> b) {
    return BoundingVolumeNode::axis_compare(a, b, 1);
}

bool BoundingVolumeNode::box_z_compare(const shared_ptr<Hittable> a, const shared_ptr<Hittable> b) {
    return BoundingVolumeNode::axis_compare(a, b, 2);
}