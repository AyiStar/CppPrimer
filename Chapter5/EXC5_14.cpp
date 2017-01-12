//
// Created by ayistar on 1/12/17.
//

// read strings from stdin.
// looking for duplicated words.
// find places in the input where one word is followed immediately by itsef.
// keep track of the largest number of times a single repetition occurs
// and which word is repeated.
// print the maximum number of duplicates,
// or else print a message saying that no word was repeated.

#include <iostream>
#include <string>
using std::string;
using std::cin;
using std::cout;
using std::endl;

int main()
{
    string last_word, curr_word, max_dup_word;
    int max_dup_times = 1, curr_dup_times = 1;

    while(cin >> curr_word){
        if(last_word == curr_word){
            ++curr_dup_times;
            if(max_dup_times < curr_dup_times){
                max_dup_times = curr_dup_times;
                max_dup_word = curr_word;
            }
        }
        else{
            curr_dup_times = 1;
        }
        last_word = curr_word;
    }

    if(max_dup_times > 1){
        cout << max_dup_word << " occurs "
             << max_dup_times << " times" << endl;
    }
    else{
        cout << "no duplicated words" << endl;
    }

    return  0;
}