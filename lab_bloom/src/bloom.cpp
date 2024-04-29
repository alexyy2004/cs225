/**
 * @file bloom.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

 #include "bloom.h"
 #include <iostream>

BF::BF(uint64_t size, std::vector<hashFunction> hashList){

    // Your code here 
    for (unsigned int i = 0; i < size; i++) {
        bv.push_back(false);
    }
    hv = hashList;
}

BF::BF(const BF& other){
    // Your code here 
    bv = other.bv;
    hv = other.hv;
}

BF::~BF(){
    return;
}

void BF::add(const int & key){

    // Your code here 
    for (hashFunction hf : hv) {
        int index = (*hf)(key) % bv.size();
        bv[index] = true;
    }
}

bool BF::contains(const int& key) const{
    // Your code here 
    for (hashFunction hf : hv) {
        int index = (*hf)(key) % bv.size();
        if (bv[index] == false) {
            return false;
        }
    }

    return true;
}

void BF::bit_union(const BF& other){
    // Your code here 
    for (unsigned int i = 0; i < bv.size(); i++) {
        if (bv[i] == true || other.bv[i] == true) {
            bv[i] = true;
        }
    }
}

void BF::intersect(const BF& other){
    // Your code here 
    for (unsigned int i = 0; i < bv.size(); i++) {
        if (bv[i] == true && other.bv[i] == true) {
            bv[i] = true;
        } else {
            bv[i] = false;
        }
    }
}

float measureFPR(std::vector<int> inList, uint64_t size, std::vector<hashFunction> hashList, unsigned max){
    // Your code here
    BF bloom_filter = BF(size, hashList);
    for (int temp : inList) {
        bloom_filter.add(temp);
    }
    float FPR = 0;
    int false_positive = 0;
    int true_negative = 0;
    for (unsigned int i = 0; i < max; i++) {
        bool flag = false;
        for (int temp : inList) {
            if ((unsigned int)temp == i) {
                flag = true;
                break;
            }
        }
        if (bloom_filter.contains(i) && !flag) {
            false_positive += 1;
        }
        if (!bloom_filter.contains(i) && !flag) {
            true_negative += 1;
        }
    }
    FPR = (float)false_positive / (false_positive + true_negative);
    return FPR;

}

bool getBitFromArray(std::vector<char> bv, int index){
    // Your code here
    int vector_index = index / 8;
    int char_index = index % 8;
    return getBitFromByte(bv[vector_index], char_index);
}

bool getBitFromByte(char in, int index){
    // Your code here
    return in >> (7 - index) & 1;

}

