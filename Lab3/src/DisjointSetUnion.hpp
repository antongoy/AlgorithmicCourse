//
// Created by anton-goy on 07.12.16.
//

#ifndef MINSPANNINGTREE_DISJOINTSETUNION_HPP
#define MINSPANNINGTREE_DISJOINTSETUNION_HPP

#include <algorithm>
#include <exception>
#include <stdexcept>
#include <random>


class DisjointSetUnion {
private:
    int max_size;
    int *predecessors;
public:
    static std::random_device rd;
    static std::mt19937 rnd_engine;
    static std::uniform_int_distribution<int> uniform_gen;

    DisjointSetUnion(int max_size);

    void make_set(int x);

    int find_set(int x);

    void unite_sets(int x, int y);

    virtual ~DisjointSetUnion();
};


#endif //MINSPANNINGTREE_DISJOINTSETUNION_HPP
