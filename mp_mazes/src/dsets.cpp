/* Your code here! */
#include "dsets.h"
#include <iostream>

void DisjointSets::addelements(int num) {
    for (int i = 0; i < num; i++) {
        elems_.push_back(-1);
    }
}

int DisjointSets::find(int elem) {
    if (elems_[elem] < 0) {
        return elem;
    }
    int root = find(elems_[elem]);
    elems_[elem] = root;
    return root;
}

void DisjointSets::setunion(int a, int b) {
    int first = find(a);
    int second = find(b);
    if (first != second) {
        int new_size = elems_[first] + elems_[second];
        if (size(first) < size(second)) {
            elems_[first] = second;
            elems_[second] = new_size;
        } else {
            elems_[second] = first;
            elems_[first] = new_size;
        }
    }
}

int DisjointSets::size(int elem) {
    // int count = 0;
    // for (unsigned int i = 0; i < elems_.size(); i++) {
    //     if (find(i) == find(elem)) {
    //         count += 1;
    //     }
    // }
    // return count;
    int index = find(elem);
    return elems_[index] * (-1);
}