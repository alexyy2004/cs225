/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>
#include <iostream>

using std::string;
using std::vector;
using std::ifstream;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    /* Your code goes here! */
    ifstream wordsFile(filename);
    string word;
    if (wordsFile.is_open()) {
        /* Reads a line from `wordsFile` into `word` until the file ends. */
        while (getline(wordsFile, word)) {
            string temp = word;
            std::sort(temp.begin(), temp.end());
            dict[word].push_back(temp);
        }
    }
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    /* Your code goes here! */
    for (const string& temp : words) {
        string s = temp;
        std::sort(s.begin(), s.end());
        dict[temp].push_back(s);
    }
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */
    vector<string> result;
    string temp = word;
    std::sort(temp.begin(), temp.end());
    for (std::pair<std::string, std::vector<std::string>> p : dict) {
        if (p.second[0] == temp) {
            result.push_back(p.first);
        }
    }
    if (result.size() != 0) {
        return result;
    }
    return vector<string>();
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
    vector<vector<string>> result;
    for (std::pair<std::string, std::vector<std::string>> p : dict) {
        vector<string> temp = get_anagrams(p.first);
        std::cout << p.first << std::endl;
        std::cout << temp.size() << std::endl;
        if (temp.size() >= 2) {
            result.push_back(temp);
        }
    }
    if (result.size() != 0) {
        return result;
    }
    return vector<vector<string>>();
}
