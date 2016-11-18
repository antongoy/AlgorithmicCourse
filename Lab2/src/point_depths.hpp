//
// Created by anton-goy on 13.11.16.
//

#ifndef LAB2_POINT_DEPTHS_HPP
#define LAB2_POINT_DEPTHS_HPP

#include <vector>
#include <deque>

#include "Point.hpp"
#include "merge_sort.hpp"

// Fill in `depth` field of each element of the array
std::vector<int> compute_depths(std::vector<Point> &points);
void compute_depths_inside(std::vector<Point> &points, long depth, std::vector<int> *depths);


#endif //LAB2_POINT_DEPTHS_HPP
