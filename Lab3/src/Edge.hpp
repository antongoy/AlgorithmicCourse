//
// Created by anton-goy on 07.12.16.
//

#ifndef MINSPANNINGTREE_EDGE_HPP
#define MINSPANNINGTREE_EDGE_HPP


class Edge {
public:
    int u;
    int v;

    double weight;

    Edge(int u, int v, double weight=0) : u(u), v(v), weight(weight) {}
};


#endif //MINSPANNINGTREE_EDGE_HPP
