//
// Created by anton-goy on 30.09.16.
//

#include "nearest_points.hpp"


std::pair<Point, Point> brute_force_search(std::vector<Point>& P) {
    long n_points = P.size();

    if (n_points == 2) {
        return std::pair<Point, Point>(P[0], P[1]);
    }

    double min_distance = FLT_MAX;
    int min_ind1 = -1, min_ind2 = -1;

    for (int i = 0; i < n_points; ++i) {
        for (int j = i + 1; j < n_points; ++j) {
            double distance = euclidean_distance(P[i], P[j]);
            if (distance <= min_distance) {
                min_distance = distance;
                min_ind1 = i;
                min_ind2 = j;
            }
        }
    }

    return std::pair<Point, Point>(P[min_ind1], P[min_ind2]);
};


std::pair<Point, Point> find_nearest_points(std::vector<Point>& points) {
    unsigned long n_points = points.size();

    std::vector<Point> X(points);

    merge_sort<Point>(X,
                      [](Point& p, Point& q) {
                          return p.x <= q.x;
                      });

    std::vector<Point> Y(X);

    for (int i = 0; i < Y.size(); ++i) {
        Y[i].index = i;
    }

    merge_sort<Point>(Y,
                      [](Point& p, Point& q) {
                          return p.y <= q.y;
                      });

    std::pair<Point, Point> nearest_points_inds = find_nearest_points_inside(X, Y);

    return nearest_points_inds;
};


std::pair<Point, Point> find_nearest_points_inside(std::vector<Point>& X,
                                                   std::vector<Point>& Y) {
    unsigned long n_points = X.size();

    if (n_points <= 3) {
        return brute_force_search(X);
    }

    unsigned long left_size = (unsigned long)(0.5 * n_points);
    unsigned long right_size = X.size() - left_size;

    auto first_x = X.begin(), last_x = X.end();

    std::vector<Point> X_left(first_x, first_x + left_size);
    std::vector<Point> X_right(first_x + left_size, last_x);

    std::vector<Point> Y_left(left_size);
    std::vector<Point> Y_right(right_size);

    unsigned long l = 0, r = 0;

    for (int j = 0; j < n_points; ++j) {
        if (Y[j].index <  left_size) {
            Y_left[l] = Y[j];
            l++;
        } else {
            Y_right[r] = Y[j];
            Y_right[r].index -= left_size;
            r++;
        }
    }

    std::pair<Point, Point> best_left_points = find_nearest_points_inside(X_left, Y_left);
    std::pair<Point, Point> best_right_points = find_nearest_points_inside(X_right, Y_right);

    double left_min_distance = euclidean_distance(best_left_points.first, best_left_points.second);
    double right_min_distance = euclidean_distance(best_right_points.first, best_right_points.second);

    double cur_min_distance;
    std::pair<Point, Point> best_points;

    if (left_min_distance <= right_min_distance) {
        cur_min_distance = left_min_distance;
        best_points = best_left_points;
    } else {
        cur_min_distance = right_min_distance;
        best_points = best_right_points;
    }

    std::vector<Point> Y_prime;

    for (int k = 0; k < n_points; ++k) {
        long index = Y[k].index;
        if (std::abs(X[index].x - X[left_size - 1].x) < cur_min_distance) {
            Y_prime.push_back(Y[k]);
        }
    }

    unsigned long n_points_in_strip = Y_prime.size();
    double distance;

    for (int i = 0; i < n_points_in_strip; ++i) {
        for (int j = i + 1; j < i + 8; ++j) {
            if (j == n_points_in_strip) {
                break;
            }

            distance = euclidean_distance(Y_prime[i], Y_prime[j]);

            if (distance < cur_min_distance) {
                cur_min_distance = distance;
                best_points = std::pair<Point, Point>(Y_prime[i], Y_prime[j]);
                best_points.first.index = X[best_points.first.index].index;
                best_points.second.index = X[best_points.second.index].index;
            }
        }
    }

    return best_points;

};


