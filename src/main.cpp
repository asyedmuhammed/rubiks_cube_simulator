#include "RubiksCube.hpp"
#include "Camera.hpp"
#include "Menu.hpp"
#include <GL/glut.h>

// Global Objects
RubiksCube rubiksCube;
Camera camera;
Menu menu(&rubiksCube);

// Mouse Control Variables
int mouseX, mouseY;  // Initial mouse position
bool isDragging = false;

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    camera.apply();

    rubiksCube.updateRotation(); // Update layer rotations
    rubiksCube.draw();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w / h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'w':  // Rotate the top layer (clockwise)
            rubiksCube.rotateLayer(1, 1, true);  // Axis: Y, Layer: 1 (Top), Clockwise: true
            break;
        case 's':  // Rotate the bottom layer (clockwise)
            rubiksCube.rotateLayer(1, -1, true);  // Axis: Y, Layer: -1 (Bottom), Clockwise: true
            break;
        case 'a':  // Rotate the left layer (clockwise)
            rubiksCube.rotateLayer(0, -1, true);  // Axis: X, Layer: -1 (Left), Clockwise: true
            break;
        case 'd':  // Rotate the right layer (clockwise)
            rubiksCube.rotateLayer(0, 1, true);  // Axis: X, Layer: 1 (Right), Clockwise: true
            break;
        case 'q':  // Rotate the front face (clockwise)
            rubiksCube.rotateLayer(2, 1, true);  // Axis: Z, Layer: 1 (Front), Clockwise: true
            break;
        case 'e':  // Rotate the back face (clockwise)
            rubiksCube.rotateLayer(2, -1, true);  // Axis: Z, Layer: -1 (Back), Clockwise: true
            break;
        case 'r':  // Rotate the top layer counterclockwise
            rubiksCube.rotateLayer(1, 1, false);  // Axis: Y, Layer: 1 (Top), Clockwise: false
            break;
        case 'f':  // Rotate the bottom layer counterclockwise
            rubiksCube.rotateLayer(1, -1, false);  // Axis: Y, Layer: -1 (Bottom), Clockwise: false
            break;
        case 'x':  // Scramble the cube
            rubiksCube.scramble();  // Call scramble function to randomize the cube
            break;
        case 'z':  // Reset the cube
            rubiksCube.reset();  // Call reset function to reset the cube
            break;
        default:
            break;
    }
}


void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            isDragging = true;
            camera.startDrag(x, y);
            mouseX = x;
            mouseY = y;
        } else if (state == GLUT_UP) {
            isDragging = false;
        }
    } else if (button == 3) { // Mouse Wheel Up (Zoom In)
        camera.zoomInOut(-0.5f); // Zoom in
    } else if (button == 4) { // Mouse Wheel Down (Zoom Out)
        camera.zoomInOut(0.5f); // Zoom out
    }
    glutPostRedisplay();
}


void motion(int x, int y) {
    if (isDragging) {
//        int deltaX = x - mouseX;
//        int deltaY = y - mouseY;

        camera.drag(x, y);



        mouseX = x;
        mouseY = y;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Rubik's Cube Simulator");

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);

    menu.create();

    glutMainLoop();
    return 0;
}
