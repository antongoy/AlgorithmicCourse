#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include <ctime>

#include "Edge.hpp"
#include "DisjointSetUnion.hpp"
#include "kruskal.hpp"

std::string parse_arguments(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Error: INPUT_FILE must be provided" << std::endl;
        std::cerr << "Usage: MinSpanningTree INPUT_FILE" << std::endl;

        exit(1);
    }

    return std::string(argv[1]);
}

std::pair<std::vector<std::string>, std::vector<Edge>> read_file(std::string filename) {
    std::fstream input_file(filename, std::fstream::in);

    std::vector<std::string> vertices;
    std::vector<Edge> edges;

    int row = -1;

    for(std::string line; std::getline(input_file, line); row++) {
        std::stringstream line_ss(line);

        int col = 0;

        for(std::string value; std::getline(line_ss, value, ','); col++) {
            if (row == -1) {
                vertices.push_back(value);
                continue;
            }

            double weight = std::stod(value);

            if (!weight) {
                continue;
            }

            edges.push_back(Edge(row, col, weight));
        }
    }

    return std::pair<std::vector<std::string>, std::vector<Edge>>(vertices, edges);
};


int main(int argc, char **argv) {
    std::string input_filename = parse_arguments(argc, argv);

    auto data = read_file(input_filename);

    auto vertices = data.first;
    auto edges = data.second;

    const int N_VERTICES = (int) vertices.size();

    clock_t begin = clock();

    auto min_spanning_tree = kruskal_algorithm(edges, N_VERTICES);

    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

    double total_sum = 0;

    for(auto const& edge: min_spanning_tree) {
        total_sum += edge.weight;
    }

    std::cout << ">>> Total weight of the min spanning tree: " << total_sum << std::endl;
    std::cout << ">>> Elapsed time: " << elapsed_secs << std::endl;

    for(auto const& edge: min_spanning_tree) {
        int u = edge.u;
        int v = edge.v;

        std::cout << "\t" << vertices[u] << "(" << u << ") - " << vertices[v] << "(" << v << ")" << std::endl;
    }

    return 0;
}