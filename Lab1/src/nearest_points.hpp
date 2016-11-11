//
// Created by anton-goy on 30.09.16.
//

#ifndef LAB1_NEAREST_POINTS_HPP
#define LAB1_NEAREST_POINTS_HPP

#include <cmath>
#include <tuple>
#include <cfloat>

#include "merge_sort.hpp"
#include "util.hpp"

std::pair<Point, Point> find_nearest_points(std::vector<Point>& points);

std::pair<Point, Point> find_nearest_points_inside(std::vector<Point>& X, std::vector<Point>& Y);

std::pair<Point, Point> brute_force_search(std::vector<Point>& P);

#endif //LAB1_NEAREST_POINTS_HPP
