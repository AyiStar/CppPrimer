//
// Created by ayistar on 1/12/17.
//

// read from cin
// count both lowercase and uppercase vowels
// count the number of blank spaces, tabs and newlines read
// count the number of ff, fl and fi

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main()
{
    char c;
    int num_vowel = 0, num_whitespace = 0, num_ff = 0, num_fi = 0, num_fl = 0;
    bool last_f = false;

    while(cin.get(c)){
        switch (c) {
            case 'i':
                if(last_f)
                    ++num_fi;
                // fall through
            case 'a': case 'A': case 'e': case'E':
            case 'I': case 'o': case'O':
            case 'u': case 'U':
                ++num_vowel;
                last_f = false;
                break;
            case ' ': case '\t': case '\n':
                ++num_whitespace;
                last_f = false;
                break;
            case 'f':
                if(last_f)
                    ++num_ff;
                last_f = true;
                break;
            case 'l':
                if(last_f)
                    ++num_fl;
                last_f = false;
                break;
            default:
                break;
        }
    }
    cout << "vowels: " << num_vowel << endl;
    cout << "whitespaces: " << num_whitespace << endl;
    cout << "\"ff\"s " << num_ff << endl;
    cout << "\"fi\"s " << num_fi << endl;
    cout << "\"fl\"s " << num_fl << endl;
    return 0;
}
