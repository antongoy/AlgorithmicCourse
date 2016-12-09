//
// Created by anton-goy on 07.12.16.
//

#include "DisjointSetUnion.hpp"

std::random_device DisjointSetUnion::rd;
std::mt19937 DisjointSetUnion::rnd_engine(rd());
std::uniform_int_distribution<int> DisjointSetUnion::uniform_gen(0, 1);

DisjointSetUnion::DisjointSetUnion(int max_size) : max_size(max_size) {
    this->predecessors = new int [max_size];

//    std::fill_n(this->predecessors, max_size, 0);
}

void DisjointSetUnion::make_set(int x) {
    if (x >= this->max_size) {
        throw std::invalid_argument("DisjointSetUnion::make_set: Argument must be less than max_size of the union");
    }

    // Now it is the predecessor for itself
    this->predecessors[x] = x;
}

int DisjointSetUnion::find_set(int x) {
    if (x >= this->max_size) {
        throw std::invalid_argument("DisjointSetUnion::find_set: Argument must be less than max_size of the union");
    }

    if (this->predecessors[x] == x) {
        return x;
    }

    this->predecessors[x] = find_set(this->predecessors[x]);

    return this->predecessors[x];
}

void DisjointSetUnion::unite_sets(int x, int y) {
    if ((x >= this->max_size) || (y >= this->max_size)) {
        throw std::invalid_argument("DisjointSetUnion::unite_sets: Arguments must be less than max_size of the union");
    }

    int root_x = find_set(x);
    int root_y = find_set(y);

    int root;
    int child;

    if (uniform_gen(rnd_engine) == 0) {
        root = root_x;
        child = root_y;
    } else {
        root = root_y;
        child = root_x;
    }

    this->predecessors[child] = root;

}

DisjointSetUnion::~DisjointSetUnion() {
    delete[] this->predecessors;
}
