#include "interval.h"

bool Interval::contains(double x) {
    return min <= x && x <= max;
}

double Interval::size() const {
    return max - min;
}

Interval Interval::expand(double delta) const {
    double padding = delta/2.0f;
    return {min - padding, max + padding};
}
