#include "triangle.h"


bool Triangle::hit(const CommonMath::Ray &r, Interval ray_t, hit_record &rec) const {
    // TODO: finish to write python experiment

    // Barycentric coords
    // Let ABC - triangle
    // I - intersection point between plane and a ray, then to find whether the intersection point is within
    // triangle let use the following barycentric coordinates:

    // alpha = 1 - (dot(AI, v) / dot(AB, v)), where v = AB - projection of AB onto CB;
    // beta = 1 - (dot(BI, v) / dot(BC, v)), where v = BC - projection of BC onto AC;
    // gamma = 1 - (dot(CI, v) / dot(CA,v)), where = v = CA - projection of CA onto BA

    return false; // To be implemented
}