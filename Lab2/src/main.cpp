#include <iostream>
#include <fstream>
#include <stack>

#include <ctime>

#include "point_depths.hpp"
#include "argparse.hpp"

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

void write_depths(std::vector<int> depths, std::string filename) {
    std::cout << ">>> Saving the depths into the file: " << filename << std::endl;
    std::fstream output_file(filename, std::fstream::out);

    // Max depth
    output_file << depths.size() << std::endl;

    for (int i = 0; i < depths.size(); ++i) {
        output_file << i << ' ' << depths[i] << std::endl;
    }
}

int main(int argc, const char **argv) {
    ArgumentParser arg_parser;

    arg_parser.appName("construct_convex_hull");
    arg_parser.addArgument("-o", "--output_file", 1);
    arg_parser.addFinalArgument("INPUT_FILE");
    arg_parser.parse((size_t) argc, argv);

    clock_t begin = clock();

    std::string filename = arg_parser.retrieve<std::string>("INPUT_FILE");
    std::string output_filename = arg_parser.retrieve<std::string>("o");

    std::vector<Point> points = read_points(filename);

    std::vector<int> depths = compute_depths(points);

    if (output_filename.compare(""))
        write_depths(depths, output_filename);

    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

    std::cout << ">>> Elapsed time: " << elapsed_secs << std::endl;

    return 0;
}