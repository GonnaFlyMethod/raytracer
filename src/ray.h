#pragma once

#include "vec3.h"

class ray{
public:
    point3 origin;
    vec3 direction;

    ray() =default;

    ray(const point3& orig, const vec3& dir)
        : origin(orig), direction(dir){}

    [[nodiscard]] point3 GetOrigin() const{
        return origin;
    }

    [[nodiscard]] vec3 GetDirection() const{
        return direction;
    }

    [[nodiscard]] point3 at(double t) const{
        auto directionWithMagnitude = t *direction;
        return (point3&)origin + (vec3&)directionWithMagnitude;
    }
};
