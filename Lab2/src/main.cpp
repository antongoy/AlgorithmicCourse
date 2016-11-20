#include <iostream>
#include <fstream>
#include <stack>

#include <ctime>

#include "point_depths.hpp"
#include "cmdparser.hpp"

std::vector<Point> read_points(std::string filename) {
    double x_coord, y_coord;
    unsigned long n_points;

    std::cout << ">>> Input file: " << filename << std::endl;
    std::fstream input_file(filename, std::fstream::in);

    input_file >> n_points;
    std::cout << ">>> Number of points in the file: " << n_points << std::endl;

    std::vector<Point> points(n_points);

    for(long i = 0; i < n_points; i++) {
        input_file >> x_coord >> y_coord;

        points[i].x = x_coord;
        points[i].y = y_coord;
    }

    input_file.close();

    return points;
}

int main(int argc, const char **argv) {
    cli::Parser arg_parser(argc, argv);

    arg_parser.set_required<std::string>("i", "input_file",
                                         "-i, --input_file \tFilename of file contained input data");
    arg_parser.set_optional<bool>("v", "verbose", false,
                                  "If true then print additional information");

    arg_parser.run_and_exit_if_error();

    std::string input_filename = arg_parser.get<std::string>("i");
    bool verbose = arg_parser.get<bool>("v");

    clock_t begin = clock();

    std::vector<Point> points = read_points(input_filename);

    std::vector<int> depths = compute_depths(points, verbose);

    std::cout << ">>> Depth table:" << std::endl;
    for (int m = 0; m < depths.size(); ++m) {
        std::cout << "\t\t  (" << m << ", " << depths[m] << ")" << std::endl;
    }

    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

    std::cout << ">>> Elapsed time: " << elapsed_secs << std::endl;

    return 0;
}