//
// Created by Антон Гой on 11.11.16.
//

#ifndef LAB2_UTILS_H
#define LAB2_UTILS_H

#include "Point.hpp"

double cross_product(Point p, Point q) {
    return p.x * q.y - p.y * q.x;
}

double is_nonleft_angle(Point p, Point q, Point r) {
    Point vector1 = Point(q.x - p.x, q.y - p.y);
    Point vector2 = Point(r.x - q.x, r.y - q.y);

    double cross_product_value = cross_product(vector1, vector2);

    return cross_product_value <= 0;
}

#endif //LAB2_UTILS_H
