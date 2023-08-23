#pragma once

class Interval {
public:
    double min;
    double max;

    Interval(double mn, double mx): min(mn), max(mx){};

    bool contains(double x);

    double size() const;

    Interval expand(double delta) const;
};
