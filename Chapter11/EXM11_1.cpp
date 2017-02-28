//
// Created by ayistar on 2/27/17.
//

#include <iostream>
#include <map>
#include <string>
#include <set>

int main()
{
    // count the number of times each word occurs in the input
    std::map<std::string, std::size_t> word_count; // empty map from string to size_t
    std::set<std::string> exclude = {"The", "But", "And", "Or", "An", "A",
                                     "the", "but", "and", "or", "an", "a"};
    std::string word;
    while( std::cin >> word) {
        // count only words that are not in exclude
        if (exclude.find(word) == exclude.end())
            ++word_count[word]; // fetch and increment the counter for word
    }
    for (const auto &w : word_count)
        std::cout << w.first << " occurs " << w.second
                  << ((w.second > 1) ? " times" : " time") << std::endl;

    return 0;
}
