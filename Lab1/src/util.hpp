//
// Created by anton-goy on 02.10.16.
//

#ifndef LAB1_UTIL_HPP
#define LAB1_UTIL_HPP

#include <cmath>
#include <iostream>

class Point {
public:
    long index;
    double x, y;

    Point() {
        this->index = 0;
        this->x = 0.0;
        this->y = 0.0;
    }

    Point(const long index, const double x, const double y) {
        this->index = index;
        this->x = x;
        this->y = y;
    }
};

double euclidean_distance(Point p, Point q);

void print_solution(Point& p, Point& q);

#endif //LAB1_UTIL_HPP
