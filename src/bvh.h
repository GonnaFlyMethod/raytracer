#pragma once

#include <algorithm>

#include "hittable.h"
#include "hittable_list.h"
#include "interval.h"
#include "ray.h"


class BoundingVolumeNode: public Hittable {
private:
    AABB bounding_box;
    shared_ptr<Hittable> left;
    shared_ptr<Hittable> right;
public:
    BoundingVolumeNode(const HittableList& list): BoundingVolumeNode(list.objects, 0, list.objects.size()){};
    BoundingVolumeNode(const std::vector<shared_ptr<Hittable>>& src_objects, size_t start, size_t end);

    virtual bool hit(const Ray& r, Interval ray_t, hit_record& rec) const override;
    virtual AABB get_bounding_box() const override;

    static bool axis_compare(const shared_ptr<Hittable> a, const shared_ptr<Hittable> b, int axis);

    static bool box_x_compare(const shared_ptr<Hittable> a, const shared_ptr<Hittable> b);
    static bool box_y_compare(const shared_ptr<Hittable> a, const shared_ptr<Hittable> b);
    static bool box_z_compare(const shared_ptr<Hittable> a, const shared_ptr<Hittable> b);
};

