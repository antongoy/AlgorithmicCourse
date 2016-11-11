#include <iostream>
#include <fstream>

#include <ctime>

#include "argparse.hpp"
#include "Point.hpp"

std::vector<Point> read_points(std::string filename) {
    double x_coord, y_coord;
    unsigned long n_points;

    std::cout << ">>> Input file: " << filename << std::endl;
    std::fstream input_file(filename, std::fstream::in);

    input_file >> n_points;

    std::vector<Point> P(n_points);

    for(long i = 0; i < n_points; i++) {
        input_file >> x_coord >> y_coord;

        P[i].x = x_coord;
        P[i].y = y_coord;
    }

    input_file.close();

    return P;
}

int main(int argc, const char **argv) {
    ArgumentParser arg_parser;

    arg_parser.appName("construct_convex_hull");
    arg_parser.addFinalArgument("INPUT_FILE");
    arg_parser.parse((size_t) argc, argv);

    clock_t begin = clock();

    std::string filename = arg_parser.retrieve<std::string>("INPUT_FILE");

    std::vector<Point> P = read_points(filename);

    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

    std::cout << elapsed_secs << std::endl;

    return 0;
}