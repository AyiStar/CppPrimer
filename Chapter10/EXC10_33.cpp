//
// Created by ayistar on 2/24/17.
//

#include <iostream>
#include <iterator>
#include <fstream>

int main()
{
    std::ifstream in_file("EXC10_33_text_file");
    if(!in_file){
        std::cout << "can't open file" << std::endl;
        return -1;
    }
    
    std::ofstream out_even_file("EXC10_33_even_file"), 
            out_odd_file("EXC10_33_odd_file");
    
    std::istream_iterator<int> in_iter(in_file), eof;
    std::ostream_iterator<int> out_even_iter(out_even_file, " \n"), 
            out_odd_iter(out_odd_file, " \n");
    
    while(in_iter != eof)
    {
        if(*in_iter % 2)
            *out_odd_iter++ = *in_iter++;
        else
            *out_even_iter++ = *in_iter++;
    }
    
    return 0;
}
