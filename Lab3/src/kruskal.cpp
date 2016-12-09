//
// Created by anton-goy on 08.12.16.
//

#include "kruskal.hpp"
#include "DisjointSetUnion.hpp"
#include "merge_sort.hpp"

std::vector<Edge> kruskal_algorithm(std::vector<Edge> edges, const int N_VERTICES) {
        DisjointSetUnion dsu(N_VERTICES);
    std::vector<Edge> min_spanning_tree;

    for (int i = 0; i < N_VERTICES; ++i) {
        dsu.make_set(i);
    }

    merge_sort<Edge>(edges,
                     [](Edge& p, Edge& q) {
                         return p.weight <= q.weight;
                     });

    for(auto const& edge: edges) {
        int u = edge.u;
        int v = edge.v;

        if (dsu.find_set(u) != dsu.find_set(v)) {
            min_spanning_tree.push_back(edge);
            dsu.unite_sets(u, v);
        }
    }

    return min_spanning_tree;
}