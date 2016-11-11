#include <iostream>
#include <fstream>
#include <vector>

#include "cmdparser.hpp"
#include "nearest_points.hpp"


int main(int argc, char** argv) {
    cli::Parser arg_parser(argc, argv);

    arg_parser.set_required<std::string>("i", "input_file", "-i, --input_file \tFilename of file contained input data");
    arg_parser.set_optional<bool>("bf", "brute_force", false,
                                  "If true then run additional brute force algorithm. For debugging purposes");

    arg_parser.run_and_exit_if_error();

    std::string input_filename = arg_parser.get<std::string>("i");
    bool is_run_brute_force = arg_parser.get<bool>("bf");

    std::cout << ">>> Input file: " << input_filename  << std::endl;

    std::fstream input_file(input_filename, std::fstream::in);

    unsigned long n_points;
    input_file >> n_points;

    std::vector<Point> P(n_points);
    double x_coord, y_coord;

    for(long i = 0; i < n_points; i++) {
        input_file >> x_coord >> y_coord;

        P[i].index = i;
        P[i].x = x_coord;
        P[i].y = y_coord;
    }

    input_file.close();

    std::pair<Point, Point> nearest_points = find_nearest_points(P);

    std::cout << ">>> Fast algorithm solution" << std::endl;
    print_solution(nearest_points.first, nearest_points.second);

    if (is_run_brute_force) {
        nearest_points = brute_force_search(P);

        std::cout << ">>> Brute force solution" << std::endl;
        print_solution(nearest_points.first, nearest_points.second);
    }

    return 0;
}