//
// Created by anton-goy on 13.11.16.
//

#include "point_depths.hpp"


double is_nonleft_angle(Point &a, Point &b, Point &c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x) <= 0;
}

std::vector<int> compute_depths(std::vector<Point> &points) {

    std::vector<int> depths;

    merge_sort<Point>(points,
                      [](Point& p, Point& q) {
                          return p.x <= q.x;
                      });

    for (int i = 0; i < points.size(); ++i) {
        points[i].is_in_hull = false;
    }

    compute_depths_inside(points, 0, &depths);

    return depths;
}

void compute_depths_inside(std::vector<Point> &points, long depth, std::vector<int> *depths) {
    std::cout << ">>> Looking for points of the depth " << depth << std::endl;

    size_t n_points = points.size();

    if (n_points <= 3) {
        std::cout << ">>> Number of points of the depth " << depth  << ": " << n_points << std::endl;
        (*depths).push_back(n_points);

        return;
    }

    std::deque<int> hull;

    double slope = (points[n_points - 1].y - points[0].y) / (points[n_points - 1].x - points[0].x);
    double intercept = - points[0].x * slope + points[0].y;

    hull.push_back(0);
    points[0].is_in_hull = true;

    int j, k;

    // Constructing lower bound of the convex hull
    for (int i = 1; i < n_points; ++i) {
        if (points[i].y - slope * points[i].x <= intercept) {
            if (hull.size() == 1) {
                hull.push_back(i);
                points[i].is_in_hull = true;
                continue;
            }

            if (hull.size() == 2) {
                if (is_nonleft_angle(points[hull[0]], points[hull[1]], points[i])) {
                    j = hull.back();
                    points[j].is_in_hull = false;
                    hull.pop_back();

                    hull.push_back(i);
                    points[i].is_in_hull = true;
                } else {
                    hull.push_back(i);
                    points[i].is_in_hull = true;
                }

                continue;
            }

            j = hull.back();
            points[j].is_in_hull = false;
            hull.pop_back();

            k = hull.back();

            while (is_nonleft_angle(points[k], points[j], points[i])) {
                j = hull.back();
                points[j].is_in_hull = false;
                hull.pop_back();

                if (hull.size() > 0) {
                    k = hull.back();
                } else {
                    break;
                }
            }

            hull.push_back(j);
            points[j].is_in_hull = true;

            hull.push_back(i);
            points[i].is_in_hull = true;
        }

    }

    // Constructing upper bound of the convex hull
    for (int i = n_points - 1; i >= 0; --i) {
        if (points[i].y - slope * points[i].x >= intercept) {
            j = hull.back();
            points[j].is_in_hull = false;
            hull.pop_back();

            k = hull.back();

            while (is_nonleft_angle(points[k], points[j], points[i])) {
                j = hull.back();
                points[j].is_in_hull = false;
                hull.pop_back();

                if (hull.size() > 0) {
                    k = hull.back();
                } else {
                    break;
                }
            }

            hull.push_back(j);
            points[j].is_in_hull = true;

            hull.push_back(i);
            points[i].is_in_hull = true;
        }
    }

    // Remove duplicated point
    hull.pop_back();

    size_t hull_size = hull.size();
    (*depths).push_back(hull_size);

    std::cout << ">>> Number of points of the depth " << depth  << ": " << hull_size << std::endl;

    if (hull_size == n_points) {
        return;
    }

    std::vector<Point> filtered_points(n_points - hull_size);

    int new_index = 0;
    for (int i = 0; i < n_points; ++i) {
        if (!points[i].is_in_hull) {
            filtered_points[new_index++] = points[i];
        }
    }

    compute_depths_inside(filtered_points, depth + 1, depths);
}
