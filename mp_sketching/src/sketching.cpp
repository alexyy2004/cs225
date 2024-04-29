#include "sketching.h"
#include <algorithm>
#include <cmath>
#include "cs225/PNG.h"

std::vector<uint64_t> kminhash(std::vector<int> inList, unsigned k, hashFunction h) {
    // std::vector<uint64_t> result (k, GLOBAL_MAX_INT);
    // // int count = 0;
    // // std::cout << "inList length: " << inList.size() << std::endl;
    // for (int i : inList) {
    //     uint64_t hash = h(i);
    //     if (hash < result.at(k - 1) && (std::find(result.begin(), result.end(), hash) == result.end())) {
    //         result.insert(result.begin(), hash);
    //         result.pop_back();
    //         std::sort(result.begin(), result.end());
    //         // std::cout << "count: " << count << std::endl;
    //         // count += 1;
    //         // for (uint64_t t : result) {
    //         //     std::cout << t << std::endl;
    //         // }
    //     }
    // }
    // return result;
    std::set<uint64_t> temp;
    for (int i : inList) {
        uint64_t hash = h(i);
        temp.insert(hash);
    }
    std::vector<uint64_t> result(temp.begin(), temp.end());
    std::sort(result.begin(), result.end());
    if (result.size() < k) {
        while (result.size() < k) {
            result.push_back(GLOBAL_MAX_INT);
        }
    } else {
        result.resize(k);
    }
    return result;
}

std::vector<uint64_t> khash_minhash(std::vector<int> inList, std::vector<hashFunction> hv) {
    std::vector<uint64_t> result;
    for (const hashFunction& hf : hv) {
        uint64_t min_hash = GLOBAL_MAX_INT;
        for (int i : inList) {
            uint64_t hash = hf(i);
            if (hash < min_hash) {
                min_hash = hash;
            }
        }
        result.push_back(min_hash);
    }
    return result;
}

std::vector<uint64_t> kpartition_minhash(std::vector<int> inList, int part_bits, hashFunction h) {
    int num_partitions = std::pow(2, part_bits);
    std::vector<uint64_t> result (num_partitions, GLOBAL_MAX_INT);
    //std::map<int, uint64_t> dict;
    for (int i : inList) {
        uint64_t hash = h(i);
        int partition_index = hash >> (64 - part_bits);
        //std::cout << "partition_index: " << partition_index << std::endl;
        if (result[partition_index] > hash) {
            result[partition_index] = hash;
        }
        // if (dict.count(partition_index)) {
        //     if (dict[partition_index] > hash) {
        //         dict[partition_index] = hash;
        //     }
        // } else {
        //     dict[partition_index] = hash;
        // }
    }
    // for (int i = 0; i < num_partitions; i++) {
    //     if (dict.count(i)) {
    //         result.push_back(dict[i]);
    //     } else {
    //         result.push_back(GLOBAL_MAX_INT);
    //     }
    // }
    // std::sort(result.begin(), result.end());
    // if ((int)result.size() < num_partitions) {
    //     for (int i = 0; i < num_partitions - (int)result.size(); i++) {
    //         result.push_back(GLOBAL_MAX_INT);
    //     }
    // }
    return result;
}

float minhash_jaccard(std::vector<uint64_t> mh1, std::vector<uint64_t> mh2) {
    std::set<uint64_t> s1(mh1.begin(), mh1.end());
    std::set<uint64_t> s2(mh2.begin(), mh2.end());
    int intersection = 0;
    int uni = 0;
    int count1 = 0;
    int count2 = 0;
    if (s1.count(GLOBAL_MAX_INT)) {
        count1 = 1;
    }
    if (s2.count(GLOBAL_MAX_INT)) {
        count2 = 1;
    }
    std::set<uint64_t> intersect;
    std::set_intersection (s1.begin(), s1.end(), s2.begin(), s2.end(), std::inserter(intersect, intersect.begin()));
    if (count1 == 1 && count2 == 1) {
        intersection = intersect.size() - 1;
    } else {
        intersection = intersect.size();
    }
    // for (uint64_t i : s1) {
    //     if (i != GLOBAL_MAX_INT && s2.count(i)) {
    //         intersection += 1;
    //     }
    // }
    uni = s1.size() + s2.size() - intersection - count1 - count2;
    return (float)intersection / uni;
}

int minhash_cardinality(std::vector<uint64_t> mh, unsigned k) {
    uint64_t k_min = mh[k - 1];
    float normalize = (float)k_min / (float)GLOBAL_MAX_INT;
    float temp = k / normalize;
    int cardinality = std::ceil(temp - 1);
    return cardinality;
}

float exact_jaccard(std::vector<int> raw1, std::vector<int> raw2) {
    std::set<int> s1(raw1.begin(), raw1.end());
    std::set<int> s2(raw2.begin(), raw2.end());
    int intersection = 0;
    int uni = 0;
    for (int i : s1) {
        if (std::find(s2.begin(), s2.end(), i) != s2.end()) {
            intersection += 1;
        }
    }
    uni = s1.size() + s2.size() - intersection;
    return (float)intersection / uni;
}

int exact_cardinality(std::vector<int> raw) {
    std::set<int> s (raw.begin(), raw.end());
    return (int)s.size();
}

MM::MM(const cs225::PNG& input, unsigned numTiles, unsigned k, hashFunction h) {
    k_ = k;
    h_ = h;
    numTiles_ = numTiles;
    width_length_ = std::ceil((double)input.width() / numTiles);
    height_length_ = std::ceil((double)input.height() / numTiles);
    //int num_elements = width_length_ * height_length_;
    std::vector<int> temp;
    std::vector<std::vector<int>> temp1(input.width(), temp);
    for (unsigned int i = 0; i < input.height(); i++) {
        vec_.push_back(temp1);
    }

    // std::vector<double> Temp;
    // std::vector<std::vector<double>> Temp1(input.width(), Temp);
    // for (unsigned int i = 0; i < input.height(); i++) {
    //     graph_.push_back(Temp1);
    // }
    // std::cout << "input_width: " << input.width() << std::endl;
    // std::cout << "width_length: " << width_length_ << std::endl;
    // std::cout << "input_height: " << input.height() << std::endl;
    // std::cout << "height_length: " << height_length_ << std::endl;
    for (unsigned int x = 0; x < input.width(); x++) {
        for (unsigned int y = 0; y < input.height(); y++) {
            BWPixel pixel = input.getPixel(x,y);
            int x_index = std::floor(x / width_length_);
            int y_index = std::floor(y / height_length_);
            int luminance = pixel.l * 255;
            vec_[x_index][y_index].push_back(luminance);
            //graph_[x_index][y_index].push_back(pixel.l);
        }
    }
}

int MM::countMatchTiles(const MM & other, float threshold) const {
    int count = 0;
    for (int x = 0; x < numTiles_; x++) {
        for (int y = 0; y < numTiles_; y++) {
            std::vector<uint64_t> tile1 = kminhash(vec_[x][y], k_, h_);
            std::vector<uint64_t> tile2 = kminhash(other.vec_[x][y], other.k_, other.h_);
            // for (int i : vec_[x][y]) {
            //     tile1.push_back(h_(i));
            // }
            // for (int i : other.vec_[x][y]) {
            //     tile2.push_back(other.h_(i));
            // }
            float jaccard = minhash_jaccard(tile1, tile2);
            //float jaccard = exact_jaccard(vec_[x][y], other.vec_[x][y]);
            if (jaccard >= threshold) {
                count += 1;
            }
        }
    }
    return count;
}

std::vector<uint64_t> MM::getMinHash(unsigned width, unsigned height) const {
    // int x_index = std::floor(width / width_length_);
    // int y_index = std::floor(height / height_length_);
    std::vector<uint64_t> result = kminhash(vec_[width][height], k_, h_);
    return result;
}

std::vector<std::tuple<int, int, int>> build_minhash_graph(std::vector<std::string> flist, unsigned numTiles, unsigned k, hashFunction h, float threshold) {
    std::vector<std::tuple<int, int, int>> graph;
    std::vector<MM*> v;
    for (std::string f : flist) {
        PNG p;
        p.readFromFile(f);
        MM* m = new MM(p, numTiles, k, h);
        v.push_back(m);
    }
    for (unsigned int i = 0; i < v.size(); i++) {
        for (unsigned int j = i + 1; j < v.size(); j++) {
            int count = v[i]->countMatchTiles(*v[j], threshold);
            std::tuple<int, int, int> tuple(i, j, count);
            graph.push_back(tuple);
        }
    }
    return graph;
}