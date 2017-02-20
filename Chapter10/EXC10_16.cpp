//
// Created by ayistar on 2/20/17.
//

#include <iostream>
#include <vector>
#include <algorithm>

void elimDups(std::vector<std::string> &words)
{
    std::sort(words.begin(), words.end());
    auto end_unique = std::unique(words.begin(), words.end());
    words.erase(end_unique, words.end());
    return;
}

std::string make_plural(size_t count,
                 const std::string &word, const std::string &suffix)
{
    std::string new_word = word;
    return (count > 1) ? (new_word + suffix) : new_word;
}


void biggies (std::vector<std::string> &words,
              std::vector<std::string>::size_type sz)
{
    elimDups(words);
    std::stable_sort(words.begin(), words.end(),
                     [] (const std::string &a, const std::string &b)
                     { return a.size() < b.size();});
    auto wc = std::partition(words.begin(), words.end(),
                           [sz] (const std::string &a)
                           {return a.size() < sz;});
    auto count = words.end() - wc;
    std::cout << count << " " << make_plural(count, "word", "s")
              << " of length " << sz << " or longer" << std::endl;
    std::for_each(wc, words.end(),
                  [] (const std::string &s)
                  {std::cout << s << " ";});
    std::cout << std::endl;

    return;
}

int main(int argc, char *argv[])
{
    std::vector<std::string> words({"Bi", "Bi", "Haoyang", "Hu", "Bing",
                                    "Bing", "Yu", "Yu", "Bihaoyang", "Hubingyu"});
    biggies(words, 4);
    return 0;
}
