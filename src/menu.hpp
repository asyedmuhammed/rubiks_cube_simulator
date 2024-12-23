#ifndef MENU_HPP
#define MENU_HPP

#include "RubiksCube.hpp"

class Menu {
private:
    RubiksCube* cube;

public:
    Menu(RubiksCube* cube);
    void create();
    static void handle(int option);
};

#endif
