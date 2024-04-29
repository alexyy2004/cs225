#include "common_words.h"

#include <iostream>
#include <fstream>
#include <cstring>
#include <stdexcept>
#include <set>
using namespace std;

bool file_exists(const string& name)
{
    ifstream f(name.c_str());
    if (f.good()) {
        f.close();
        return true;
    } else {
        f.close();
        return false;
    }
}

const string USAGE =
"USAGE: find_common_words [TEXT FILE ..] -n [NUM] -o [FILE]\n"
"Finds all words who appear >= n times in ALL the parameter text files.";

int main(int argc, char* argv[])
{
    // vector<string> in_files;
    // string out_filename = "";
    // unsigned int n = 0;
    // for (int i = 1; i < argc; i++) {
    //     if (strcmp(argv[i], "-o") == 0) {
    //         i++;
    //         if (i != argc) {
    //             out_filename = argv[i];
    //         }
    //     } else if (strcmp(argv[i], "-n") == 0) {
    //         i++;
    //         if (i != argc) {
    //             /* stoi() will except for non-numeric values. */
    //             try {
    //                 n = stoi(argv[i]);
    //             } catch (invalid_argument& e) {
    //                 cerr << USAGE << endl;
    //                 return -1;
    //             } catch (out_of_range& e) {
    //                 cerr << "Number too large to take as input." << endl;
    //                 return -1;
    //             }
    //         }
    //     } else if (file_exists(argv[i])) {
    //         in_files.push_back(argv[i]);
    //     } else {
    //         cerr << "Could not read file: " << argv[i] << endl;
    //     }
    // }
    // CommonWords cw(in_files);
    // vector<string> words = cw.get_common_words(n);
    // /* Redirect cout to be a file. */
    // ofstream out(out_filename);
    // if (out.good()) {
    //     cout.rdbuf(out.rdbuf());
    // }
    // for (string& str : words) {
    //     cout << str << endl;
    // }
    // if (in_files.empty()) {
    //     cerr << USAGE << endl;
    // }
    // return 0;
    vector<string> in;
    in.push_back("../data/small1.txt");
    in.push_back("../data/small2.txt");
    CommonWords cw(in);
    vector<string> students = cw.get_common_words(999);
    set<string> resultSet(students.begin(), students.end());
    set<string> canon = {};
    //REQUIRE(canon == resultSet);
    for (string s : resultSet) {
        std::cout << s << std::endl;
    }

    in.clear();
    in.push_back("../data/PrideAndPrejudice.txt");
    in.push_back("../data/Beowulf.txt");
    cw = CommonWords(in);
    students = cw.get_common_words(999);
    set<string> resultSet2(students.begin(), students.end());
    canon = {"of", "the"};
    //REQUIRE(canon == resultSet2);
    std::cout << "------------" << std::endl;
    for (string s : resultSet2) {
        std::cout << s << std::endl;
    }
}
