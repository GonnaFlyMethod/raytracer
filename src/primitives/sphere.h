#pragma once

#include "../hittable.h"
#include "../common_math/vec3.h"
#include "../aabb.h"
#include "../common_math/ray.h"

class Sphere: public Hittable{
private:
    CommonMath::Point3 center1;

    CommonMath::Vec3 blending_vec_to_center2;

    bool is_moving;

    double radius;
    std::shared_ptr<Material> mat_ptr;

    AABB bounding_box;

    CommonMath::Point3 center(double time) const;


    // TODO: test the function output with a different input

    // p: A point on unit sphere with radius one. The sphere is centered at the origin
    // The point is given in Cartesian coordinates
    // u: returned value [0; 1] of angle around Y axis from X = -1
    // v: returned value [0; 1] of angle from Y=-1 to Y=1;

    //     <X: 1, Y: 0, Z: 0> yields <u: 0.50, v: 0.50>       <X: -1, Y: 0, Z: 0> yields <u: 0.00, v: 0.50>
    //     <X: 0, Y: 1, Z: 0> yields <u: 0.50, v: 1.00>       <X: 0, Y: -1, Z: 0> yields <u: 0.50, v: 0.00>
    //     <X: 0, Y: 0, Z: 1> yields <u: 0.25, v: 0.50>        <X: 0, Y: 0, Z: -1> yields <u: 0.75, v: 0.50>
    static void get_sphere_uv(const CommonMath::Point3& p, double& u, double& v);

public:
    // Stationary sphere
    Sphere(CommonMath::Point3 cen, double r, std::shared_ptr<Material> m);

    // Moving sphere
    Sphere(CommonMath::Point3 cen1, CommonMath::Point3 cen2, double r, std::shared_ptr<Material> m);

    virtual bool hit(const CommonMath::Ray& r, Interval ray_t, hit_record& rec) const;
    virtual AABB get_bounding_box() const override;
};
