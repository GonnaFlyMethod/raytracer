#pragma once

#include "../hittable.h"
#include "placeable_on_plane.h"
#include "../camera.h"

class Triangle: public Hittable, public PlaceableOnPlane{
private:
    CommonMath::Point3 vertex0;
    CommonMath::Point3 vertex1;
    CommonMath::Point3 vertex2;

    CommonMath::Vec3 vertex0_vertex1_edge;
    CommonMath::Vec3 vertex1_vertex2_edge;
    CommonMath::Vec3 vertex2_vertex0_edge;

    std::shared_ptr<Material> mat_ptr;

    Camera cam;

    double left_x_for_projection,
           right_x_for_projection,
           bottom_y_for_projection,
           top_y_for_projection,
           farthest_z_for_projection;

    CommonMath::Vec3 vertex0_in_local_space;
    CommonMath::Vec3 vertex1_in_local_space;
    CommonMath::Vec3 vertex2_in_local_space;

public:
    Triangle(
            CommonMath::Point3 vertexA,
            CommonMath::Point3 vertexB,
            CommonMath::Point3 vertexC,
            std::shared_ptr<Material> _mat_ptr, Camera& camera);

    AABB get_bounding_box() const override;
    void adjust_to_image_dimensions(double image_width, double image_height);

    bool hit(const CommonMath::Ray& r, Interval ray_t, hit_record& rec) const override;
};

