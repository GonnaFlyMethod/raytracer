#include "interval.h"

bool Interval::contains(double x) {
    return min <= x && x <= max;
}