#pragma once

#include <cmath>

class Interval {
public:
    double min;
    double max;

    Interval(double mn, double mx): min(mn), max(mx){};
    Interval(Interval& intervalA, Interval& intervalB)
        : min(fmin(intervalA.min, intervalB.min)),
        max(fmax(intervalA.max, intervalB.max)){};
    bool contains(double x);

    double size() const;

    Interval expand(double delta) const;
};
