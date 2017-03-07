//
// Created by ayistar on 3/7/17.
//

#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <string>
#include <exception>

void word_transform (std::ifstream &map_file, std::ifstream &input);
std::map<std::string, std::string> buildMap (std::ifstream &map_file);
const std::string &
transform (const std::string &s, const std::map<std::string, std::string> &m);


int main()
{
    std::ifstream map_file("EXM11_3_map_file");
    if(!map_file){
        std::cout << "can't open file" << std::endl;
        return -1;
    }
    std::ifstream input_file("EXM11_3_input_file");
    if(!input_file){
        std::cout << "can't open file" << std::endl;
        return -1;
    }

    word_transform(map_file, input_file);

    return 0;
}


// overall processing manage
void word_transform (std::ifstream &map_file, std::ifstream &input)
{
    auto trans_map = buildMap (map_file); // store the transformation
    std::string text; // hold each line from the input
    while (std::getline(input, text)) // read a line of input
    {
        std::istringstream stream(text); // read each word
        std::string word;
        bool firstword = true; // control whether a space is printed

        while(stream >> word)
        {
            if (firstword)
                firstword = false;
            else
                std::cout << " "; // print a space between words
            // transform returns its first argument or its transformation
            std::cout << transform(word, trans_map); // print the output
        }
        std::cout << std::endl;
    }
}

std::map<std::string, std::string>
buildMap (std::ifstream &map_file)
{
    std::map<std::string, std::string> trans_map; // hold the transformations
    std::string key; // a word to transform
    std::string value; // phrase to use instead
    // read the first word into key and the rest of the line into value
    while ((map_file >> key) && std::getline(map_file, value))
    {
        if (value.size() > 1) // check that there is a transformation
        {
            trans_map[key] = value.substr(1); // skip leading space
            // std::cout << key + " " + value << std::endl;
        }
        else
            throw std::runtime_error("no rule for " + key);
    }
    return trans_map;
}

const std::string &
transform (const std::string &s, const std::map<std::string, std::string> &m)
{
    // the actual map work; this part is the heart of the program
    auto map_it = m.find(s);
    // if this word is in the transformation map
    if (map_it != m.cend())
        return map_it->second; // use the replacement word
    else
        return s; // otherwise return the original unchanged
}