//
// Created by ayistar on 2/23/17.
//


#include <iostream>
#include <iterator>
#include <vector>

int main()
{
    std::istream_iterator<int> in_iter(std::cin); // read ints from cin
    std::istream_iterator<int> eof; // istream "end" iterator

    std::vector<int> vec;
    while(in_iter != eof) { //while there's valid input to read
        // postfix increment reads the stream and returns the old value of the iterator
        // we dereference that iterator to get the previous value from the stream
        vec.push_back(*in_iter++);
    }
    for(const auto &i : vec)
        std::cout << i << " ";
    std::cout << std::endl;

    return 0;
}