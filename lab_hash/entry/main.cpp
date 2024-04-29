#include <iostream>

#include "lphashtable.h"
#include "schashtable.h"
#include "dhhashtable.h"

#include <catch2/catch_test_macros.hpp>

#include "cs225/textfile.h"
#include "schashtable.h"

#include <algorithm>
#include <map>
#include <vector>

int main()
{
    std::cout << "This main file is for you to write and run your own test cases." << std::endl;
    std::cout << "To run the provided test cases, run `./test`" << std::endl;
    // feel free to insert manual test cases here
    TextFile infile("../data/textEasy.txt");
	LPHashTable<std::string, int> hashTable(32);
	int val = 0;
	while (infile.good())
	{
		val++;
		std::string word = infile.getNextWord();
		hashTable.insert(word, val);
	}
	if (!hashTable.keyExists("all"))
		//FAIL("Did not insert key: 'all'");
	//if (!hashTable.keyExists("base"))
		//FAIL("Did not insert key: 'base'");
	//if (hashTable.find("are") != 4)
		//FAIL("Did not insert key-value pair properly");

	//REQUIRE(true);


    return 0;
}
