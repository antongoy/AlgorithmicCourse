//
// Created by anton-goy on 10.11.16.
//

#ifndef LAB2_POINT_HPP
#define LAB2_POINT_HPP

#include <cmath>

class Point {
public:
    double x, y;

    bool is_in_hull;

    Point() : x(0), y(0), is_in_hull(false) {}
    Point(const double x, const double y) : x(x), y(y), is_in_hull(false) {}

    // Compute cosine between points `p` and `q`
    friend double compute_cosine(Point p, Point q) {
        double norm_p = sqrt(p.x * p.x + p.y * p.y);
        double norm_q = sqrt(q.x * q.x + q.y * q.y);

        return (p.x * q.x + p.y * q.y) / (norm_p * norm_q);
    }

    friend Point operator-(Point &p, Point &q) {
        return Point(p.x - q.x, p.y - q.y);
    }

    friend Point operator+(Point &p, Point &q) {
        return Point(p.x + q.x, p.y + q.y);
    }
};


#endif //LAB2_POINT_HPP
