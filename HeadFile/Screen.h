//
// Created by ayistar on 1/17/17.
//

#ifndef CPPPRIMER_SCREEN_H
#define CPPPRIMER_SCREEN_H

#include <iostream>
#include <string>

#include "Window_manager.h"

// class Window_manager;

class Screen {
    friend class Window_manager;
//    friend void Window_manager::clear(Window_manager::ScreenIndex);

public:
    typedef std::string::size_type pos;

    Screen() = default;
    Screen(pos ht, pos wd, char c):
            height(ht), width(wd), contents(ht * wd, c){}
    Screen(pos ht, pos wd):
            height(ht), width(wd), contents(ht *wd, ' '){}

    char get() const {return contents[cursor]; }
    inline char get(pos ht, pos wd) const;
    Screen &move(pos r, pos c);

    Screen &set(char);
    Screen &set(pos, pos, char);

    Screen &display(std::ostream &os) { do_display(os); return *this; }

    void some_member()const;
    mutable size_t access_ctr;
private:
    pos cursor = 0;
    pos height = 0, width = 0;
    std::string contents;

    void do_display(std::ostream &os) const { os << contents; }
};

inline Screen &Screen::move(pos r, pos c)
{
    pos row = r * width; // compute the row location
    cursor = row + c; // move the cursor to the column within tht row
    return *this;
}

char Screen::get(pos r, pos c) const
{
    pos row = r * width;
    return contents[row + c];
}

void Screen::some_member() const
{
    ++access_ctr;
}

Screen &Screen::set(char c)
{
    contents[cursor] = c;
    return *this;
}

Screen &Screen::set(pos row, pos col, char ch)
{
    contents[row * width + col] = ch;
    return *this;
}

/*void Window_manager::clear(ScreenIndex i)
{
    Screen &s = screens[i];
    s.contents = std::string(s.height * s.width, ' ');
}*/
#endif //CPPPRIMER_SCREEN_H
