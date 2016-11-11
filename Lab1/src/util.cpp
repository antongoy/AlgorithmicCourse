//
// Created by anton-goy on 03.10.16.
//

#include "util.hpp"

double euclidean_distance(Point p, Point q) {
    return std::sqrt((p.x - q.x) * (p.x - q.x) +
                     (p.y - q.y) * (p.y - q.y));
}

void print_solution(Point& p, Point& q) {
    if (p.index > q.index) {
        std::swap(p, q);
    }

    std::cout << "\tFirst point: (" << p.x << ", " << p.y << ") in position " << p.index + 1 << std::endl;
    std::cout << "\tSecond point: (" << q.x << ", " << q.y << ") in position " << q.index + 1 << std::endl;
    std::cout << "\tDistance: " << euclidean_distance(p, q) << std::endl;
}