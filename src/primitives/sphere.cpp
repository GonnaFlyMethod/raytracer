#include "sphere.h"
#include "../common_math.h"

Sphere::Sphere(Point3 cen, double r, shared_ptr<Material> m):  center1(cen), radius(r), mat_ptr(m){
    Vec3 radius_vec = Vec3(r, r, r);
    this->bounding_box = AABB(cen - radius_vec, cen + radius_vec);
}

Sphere::Sphere(Point3 cen1, Point3 cen2, double r, shared_ptr<Material> m)
    : center1(cen1),
      radius(r),
      mat_ptr(m),
      is_moving(true),
      blending_vec_to_center2(cen2 - cen1){

    Vec3 rvec = Vec3(r,r,r);
    AABB box1 = AABB(cen1 - rvec, cen1 + rvec);
    AABB box2 = AABB(cen2 - rvec, cen2 + rvec);

    this->bounding_box = AABB(box1, box2);
}

void Sphere::get_sphere_uv(const Point3 &p, double &u, double &v) {
    double theta = acos(-p.y());
    double phi = atan2(-p.z(), p.x()) + pi;

    u = phi / (2*pi);
    v = theta / pi;
}


AABB Sphere::get_bounding_box() const{
    return this->bounding_box;
}

Point3 Sphere::center(double time) const {
    return center1 + time*blending_vec_to_center2;
}

bool Sphere::hit(const Ray& r, Interval ray_t, hit_record& rec) const{
    Point3 current_center = this->is_moving ? center(r.GetTime()) : center1;

    Vec3 cr = r.GetOrigin() - current_center;

    double a = r.GetDirection().length_squared();
    double half_b = dot(cr, r.GetDirection());
    double c = cr.length_squared() - this->radius * this->radius;

    double discriminant = half_b * half_b - a*c;

    if (discriminant < 0){
        return false;
    }

    double root = (-half_b - sqrt(discriminant) ) / a;

    if (root < ray_t.min || root > ray_t.max){
        root = (-half_b + sqrt(discriminant) ) / a;

        if (root < ray_t.min || root > ray_t.max){
            return false;
        }
    }

    rec.t = root;
    rec.p = r.at(rec.t);

    Vec3 outward_normal = (rec.p - current_center) / this->radius;

    rec.set_face_normal(r, outward_normal);
    this->get_sphere_uv(outward_normal, rec.u, rec.v);
    rec.mat_ptr = this->mat_ptr;

    return true;
}