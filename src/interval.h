#pragma once

class Interval {
private:
    double min;
    double max;
public:
    Interval(double mn, double mx): min(mn), max(mx){};

    bool contains(double x);
};
