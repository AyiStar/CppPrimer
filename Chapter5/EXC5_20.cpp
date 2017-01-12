//
// Created by ayistar on 1/12/17.
//

// read a sequence of strings from stdin
// until either the same word occurs twice in succession
// or all the words have been read

// use a while loop to read the text one word at a time
// use the break statement to terminate the loop
// if a word occurs twice in succession

// print the word if it occurs twice in succession
// or else print a message saying that no word was repeated

#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main()
{
    string last_word, curr_word;
    bool repeat = false;

    while(cin >> curr_word){
        if(last_word == curr_word){
            repeat = true;
            break;
        }
        last_word = curr_word;
    }

    if(repeat)
        cout << curr_word << " has repeated in succession" << endl;
    else
        cout << "no word was repeated" << endl;

    return 0;
}
