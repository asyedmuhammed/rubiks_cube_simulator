#include "Menu.hpp"
#include <GL/glut.h>
#include <iostream>

static RubiksCube* globalCube = NULL;

Menu::Menu(RubiksCube* cube) : cube(cube) {
    globalCube = cube;
}

void Menu::create() {
    glutCreateMenu(handle);
    glutAddMenuEntry("Reset Cube", 1);
    glutAddMenuEntry("Scramble Cube", 2);
    glutAddMenuEntry("Exit", 0);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void Menu::handle(int option) {
    switch (option) {
        case 1:
            globalCube->reset();
            break;
        case 2:
            globalCube->scramble();
            break;
        case 0:
            exit(0);
            break;
    }
    glutPostRedisplay();
}
