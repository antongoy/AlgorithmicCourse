//
// Created by anton-goy on 27.09.16.
//

#ifndef LAB1_MERGE_SORT_HPP
#define LAB1_MERGE_SORT_HPP

#include <iostream>
#include <iterator>
#include <exception>
#include <vector>

template <typename T>
void merge(std::vector<T>& array, std::vector<T>& auxiliary_array,
           unsigned long l_begin, unsigned long l_end,
           unsigned long r_begin, unsigned long r_end,
           bool (*cmpr)(T&, T&)) {

    for (auto i = l_begin; i <= r_end; i++) {
        auxiliary_array[i] = array[i];
    }

    auto l = l_begin, r = r_begin;

    for (auto i = l_begin; i <= r_end; i++) {
        if (l > l_end) {
            array[i] = auxiliary_array[r];
            r++;
            continue;
        }

        if (r > r_end) {
            array[i] = auxiliary_array[l];
            l++;
            continue;
        }

        if (cmpr(auxiliary_array[l], auxiliary_array[r])) {
            array[i] = auxiliary_array[l];
            l++;
        } else {
            array[i] = auxiliary_array[r];
            r++;
        }
    }

}


template <typename T>
void merge_sort_inside(std::vector<T>& array, std::vector<T>& auxiliary_array,
                       unsigned long begin, unsigned long end,
                       bool (*cmpr)(T&, T&)){

    if (begin <  end) {
        unsigned long l_begin = begin, l_end = 0.5 * (begin + end), r_begin = l_end + 1, r_end = end;

        merge_sort_inside(array, auxiliary_array, l_begin, l_end, cmpr);
        merge_sort_inside(array, auxiliary_array, r_begin, r_end, cmpr);
        merge(array, auxiliary_array, l_begin, l_end, r_begin, r_end, cmpr);
    }
}

template <typename T>
std::vector<T> merge_sort(std::vector<T>& array, bool (*cmpr)(T&, T&))  {
    unsigned long array_size = array.size();

    if (!array_size) {
        throw std::invalid_argument("There are no elements in array to sort.");
    }

    std::vector<T> auxiliary_array(array);

    merge_sort_inside(array, auxiliary_array, 0, array_size - 1, cmpr);

    return array;
}

#endif //LAB1_MERGE_SORT_HPP
