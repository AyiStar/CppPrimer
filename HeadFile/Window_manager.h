//
// Created by ayistar on 1/17/17.
//

#ifndef CPPPRIMER_WINDOW_MANAGER_H
#define CPPPRIMER_WINDOW_MANAGER_H

#include "Screen.h"
#include <vector>



class Window_manager {

public:
    using ScreenIndex = std::vector<Screen>::size_type;

    void clear(ScreenIndex); // reset the Screen at the given position to all blanks
    ScreenIndex addScreen(const Screen&); // add a Screen to the window and return its index

private:
    std::vector<Screen> screens{Screen(24,80,' ')};
};


void Window_manager::clear(ScreenIndex i)
{
    Screen &s = screens[i];
    s.contents = std::string(s.height * s.width, ' ');
}

Window_manager::ScreenIndex Window_manager::addScreen(const Screen &s)
{
    screens.push_back(s);
    return screens.size() - 1;
}


#endif //CPPPRIMER_WINDOW_MANAGER_H
